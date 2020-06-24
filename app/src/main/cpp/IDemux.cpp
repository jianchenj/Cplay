//
// Created by Administrator on 2020/6/15.
//

#include "IDemux.h"
#include "CLog.h"

void IDemux::Main() {
    CThread::Main();
    while (!isExit) {
        CData d = Read();
        //CLOGI("IDemux Read %d", d.size);
        if (d.size > 0) {
            Notify(d);
        } else {
            break;
        }
    }
}
