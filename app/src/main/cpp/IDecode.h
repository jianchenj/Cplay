//
// Created by Administrator on 2020/6/23.
//

#ifndef CPLAY_IDECODE_H
#define CPLAY_IDECODE_H

#include "CParameter.h"
#include "IObserver.h"
#include <list>

//解码接口，支持硬解码
class IDecode : public IObserver{
public:

    virtual bool Open(CParameter para) = 0;

    //future模型 发送数据到线程解码
    virtual bool sendPacket(CData pkt) = 0;

    //从线程中获取解码结果, 再次调用会复用上次空间,线程不安全
    virtual CData RecvFrame() = 0;

    //由观察者主体notify的数据 阻塞
    virtual void Update(CData pkt);

    bool isAudio = false;

    //缓冲队列最大值(以帧数做单位)，另外种方法是以容量大小
    int maxList = 100;

protected:
    virtual void Main();
    //缓冲队列
    std::list<CData> packs;
    std::mutex packMutex;
};


#endif //CPLAY_IDECODE_H
