//
// Created by Administrator on 2020/6/15.
//

#include "FFDemux.h"
#include "CLog.h"

extern "C" {
#include "libavformat/avformat.h"
#include "libavutil/avutil.h"
}

//打开文件，todo 目前米有考虑线程安全
bool FFDemux::Open(const char *url) {
    CLOGI("FFDemux <Open> file %s", url);
    int re = avformat_open_input(&ic, url, 0, 0);
    if (re != 0) {
        char buf[1024] = {0};
        av_strerror(re, buf, sizeof(buf));
        CLOGE("FFDemux :: <Open> avformat_open_input %s failed", url);
        return false;
    }
    CLOGI("FFDemux :: <Open> avformat_open_input %s success", url);

    //读取文件信息
    re = avformat_find_stream_info(ic, 0);
    if (re != 0) {
        char buf[1024] = {0};
        av_strerror(re, buf, sizeof(buf));
        CLOGE("FFDemux :: <Open> avformat_find_stream_info %s failed", url);
        return false;
    }
    this->totalMs = ic->duration / (AV_TIME_BASE / 1000);//这个值不一定有，有的参数是存在stream里的
    CLOGI("FFDemux :: <Open> totalMs = %d", totalMs);
    return true;
}

CData FFDemux::Read() {
    if (!ic)
        return CData();
    CData d;
    AVPacket *pkt = av_packet_alloc();
    int re = av_read_frame(ic, pkt);
    if (re != 0) {
        //每次中途return的时候，要注意有没有空间没有释放
        av_packet_free(&pkt);
        return CData();
    }
    //CLOGI("FFDemux :: <Read> pack size : %d, pts %lld", pkt->size, pkt->pts);
    d.data = (unsigned char *) pkt;
    d.size = pkt->size;
    return d;
}

FFDemux::FFDemux() {//构造函数
    static bool isFirst = true;
    if (isFirst) {
        //只初始化一次

        isFirst = false;
        //注册所有解封装器
        av_register_all();

        //注册所有解码器
        avcodec_register_all();

        //初始化网络
        avformat_network_init();

        CLOGD("register FFmpeg");
    }
}

CParameter FFDemux::GetPara() {
    CLOGI("********* FFDemux <GetPara> ********");
    if (!ic) {
        return CParameter();
    }
    //获取视频流索引
    int re = av_find_best_stream(ic, AVMEDIA_TYPE_VIDEO, -1, -1, 0, 0);
    if (re < 0) {
        CLOGI("FFDemux:: <GetPara> av_find_best_stream failed");
        return CParameter();
    }
    CParameter para;
    para.para = ic->streams[re]->codecpar;
    return para;
}
