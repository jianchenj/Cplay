//
// Created by Administrator on 2020/6/23.
//

#ifndef CPLAY_IOBSERVER_H
#define CPLAY_IOBSERVER_H

#include "CData.h"
#include "CThread.h"
#include <vector>
#include <mutex>

//观察者 和 主体
class IObserver : public CThread{
public:
    //观察者接收数据函数
    virtual void Update(CData data) {}

    //主体函数
    void AddObs(IObserver *observer);

    //通知所有观察者
    void Notify(CData data);

protected:
    std::vector<IObserver *> obss;//容器
    std::mutex mux;//互斥锁
};


#endif //CPLAY_IOBSERVER_H
