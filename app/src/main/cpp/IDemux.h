//
// Created by Administrator on 2020/6/15.
//

#ifndef CPLAY_IDEMUX_H
#define CPLAY_IDEMUX_H

#include "CData.h"
#include "CThread.h"
#include "IObserver.h"
#include "CParameter.h"

//解封装接口类
class IDemux : public IObserver{
public:
    //打开文件 or 流媒体  rtmp http rtsp
    virtual bool Open(const char *url) = 0;

    //获取视频参数
    virtual CParameter GetPara()  = 0;

    //读取一帧数据，数据由调用者清理
    virtual CData Read() = 0;

    //总时长(ms)
    int totalMs = 0;

protected:
    virtual void Main();

};


#endif //CPLAY_IDEMUX_H
