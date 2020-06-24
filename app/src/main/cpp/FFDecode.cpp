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

    //3.打开解码器
    int re = avcodec_open2(codec, 0, 0);
    if (re != 0) {
        char buff[1024] = {0};
        av_strerror(re, buff, sizeof(buff) - 1);
        return false;
    }
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
    int re = avcodec_send_packet(codec, (AVPacket *) pkt.data);
    return true;
}

CData FFDecode::RecvFrame() {
    return CData();
}
