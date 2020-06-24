//
// Created by Administrator on 2020/6/15.
//

#ifndef CPLAY_FFDEMUX_H
#define CPLAY_FFDEMUX_H


#include "CData.h"
#include "IDemux.h"
struct AVFormatContext;
class FFDemux : public IDemux {
public:
    //打开文件 or 流媒体  rtmp http rtsp
    virtual bool Open(const char *url);

    //读取一帧数据，数据由调用者清理
    virtual CData Read();

    //获取视频参数
    virtual CParameter GetPara();

    FFDemux();

private:
    AVFormatContext *ic = 0;
};


#endif //CPLAY_FFDEMUX_H
