//
// Created by Administrator on 2020/6/23.
//

#ifndef CPLAY_FFDECODE_H
#define CPLAY_FFDECODE_H


#include "CParameter.h"
#include "IDecode.h"

struct AVCodecContext;
struct AVFrame;
class FFDecode : public IDecode {
public:
    virtual bool Open(CParameter para);

    //future模型 发送数据到线程解码
    virtual bool sendPacket(CData pkt);

    //从线程中获取解码结果, 再次调用会复用上次空间,线程不安全
    virtual CData RecvFrame();

protected:
    AVCodecContext *codec = 0;
    AVFrame *frame = 0;
};


#endif //CPLAY_FFDECODE_H
