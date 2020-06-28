//
// Created by Administrator on 2020/6/23.
//

extern "C" {
#include <libavcodec/avcodec.h>
}

#include "CLog.h"
#include "FFDecode.h"


bool FFDecode::Open(CParameter para) {
    CLOGI("********** IDecode:: <Open> *************");
    if (!para.para)
        return false;
    AVCodecParameters *p = para.para;
    //1.查找解码器
    AVCodec *cd = avcodec_find_decoder(p->codec_id);
    if (!cd) {
        CLOGE("IDecode:: <Open> avcodec_find_decoder failed!");
        return false;
    }
    CLOGI("IDecode:: <Open> avcodec_find_decoder success!");

    //2.创建解码上下文, 并复制参数
    codec = avcodec_alloc_context3(cd);
    avcodec_parameters_to_context(codec, p);
    codec->thread_count = 8;//多线程解码
    //3.打开解码器
    int re = avcodec_open2(codec, 0, 0);
    if (re != 0) {
        char buff[1024] = {0};
        av_strerror(re, buff, sizeof(buff) - 1);
        return false;
    }
    isAudio = !(codec->codec_type == AVMEDIA_TYPE_VIDEO);
    CLOGI("********** IDecode:: <Open> success! *************");
    return true;
}

bool FFDecode::sendPacket(CData pkt) {
    if (pkt.size <= 0 || !pkt.data) {
        return false;
    }
    if (!codec) {
        return false;
    }
    return avcodec_send_packet(codec, (AVPacket *) pkt.data) == 0;

}

CData FFDecode::RecvFrame() {
    if (!codec) return CData();
    if (!frame) {
        frame = av_frame_alloc();
    }
    int re = avcodec_receive_frame(codec, frame);
    if (re != 0) {
        return CData();//解码失败
    }

    CData d;
    d.data = (unsigned char *) frame;
    if (codec->codec_type == AVMEDIA_TYPE_VIDEO) {
        //前提这是个yuv视频, Y, U , V 平面格式三路行的大小，乘以高度 就是视频帧大小, linesize本身8位最多
        d.size = (frame->linesize[0] + frame->linesize[1] + frame->linesize[2]) * frame->height;
        d.isAudio = false;
        return d;
    } else if (codec->codec_type == AVMEDIA_TYPE_AUDIO) {
        // 样本字节数* 单通道样本数 * 通道数
        d.size = av_get_bytes_per_sample((AVSampleFormat) frame->format) * frame->nb_samples * 2;
        d.isAudio = true;
        return d;
    }
    return CData();
}
