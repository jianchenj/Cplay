//
// Created by Administrator on 2020/6/23.
//

#include "IDecode.h"
#include "CLog.h"

void IDecode::Update(CData pkt) {
    if (pkt.isAudio != isAudio) {
        return;
    }

    while (!isExit) {
        //数据进缓冲队列
        packMutex.lock();
        //list数量过多
        if (packs.size() < maxList) {
            //生产者
            packs.push_back(pkt);
            packMutex.unlock();
            break;
        }
        packMutex.unlock();
        CSleep(1);
    }


}


void IDecode::Main() {
    while (!isExit) {
        packMutex.lock();
        if (packs.empty()) {
            packMutex.unlock();
            CSleep(1);
            continue;
        }
        //从队列中取数据, 消费者
        CData pack = packs.front();
        packs.pop_front();

        if (this->sendPacket(pack)) {//发送数据到解码线程
            //一次send可能出现多次receive，一个数据包可能包含多个解码结果
            while (!isExit) {
                //获取解码数据
                CData frame = RecvFrame();
                if (!frame.data) {
                    break;
                }

                this->Notify(frame);//发送数据给观察者
            }

        }

        pack.drop();

        packMutex.unlock();
    }

}

