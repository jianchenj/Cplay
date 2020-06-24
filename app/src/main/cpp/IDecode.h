//
// Created by Administrator on 2020/6/23.
//

#ifndef CPLAY_IDECODE_H
#define CPLAY_IDECODE_H

#include "CParameter.h"
#include "IObserver.h"

//解码接口，支持硬解码
class IDecode : public IObserver{
public:

    virtual bool Open(CParameter para) = 0;

    //future模型 发送数据到线程解码
    virtual bool sendPacket(CData pkt) = 0;

    //从线程中获取解码结果
    virtual CData RecvFrame() = 0;
};


#endif //CPLAY_IDECODE_H
