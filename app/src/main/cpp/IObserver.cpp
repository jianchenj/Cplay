//
// Created by Administrator on 2020/6/23.
//

#include "IObserver.h"

void IObserver::AddObs(IObserver *observer) {
    if (!observer) return;
    mux.lock();
    obss.push_back(observer);
    mux.unlock();
}

void IObserver::Notify(CData data) {
    mux.lock();
    int size = obss.size();
    for (int i = 0; i < size; i++) {
        obss[i]->Update(data);
    }
    mux.unlock();
}

