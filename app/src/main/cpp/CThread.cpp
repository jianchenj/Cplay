//
// Created by Administrator on 2020/6/23.
//

#include "CThread.h"
#include "CLog.h"
#include <thread>

using namespace std;

void CSleep(int mis) {
    chrono::microseconds du(mis);
    this_thread::sleep_for(du);
}

void CThread::Start() {
    isExit = false;
    thread th(&CThread::ThreadMain, this);
    th.detach();//当前线程放弃对启动的线程的控制
}


void CThread::ThreadMain() {
    CLOGI("线程函数进入");
    isRunning = true;
    Main();
    isRunning = false;
    CLOGI("线程函数结束");
}

void CThread::Stop() {
    isExit = true;
    for (int i = 0; i <200 ; i++) {
        if (!isRunning) {
            CLOGI("线程停止成功");
            return;
        }
        CSleep(1);
    }
    CLOGE("线程停止超时");
}
