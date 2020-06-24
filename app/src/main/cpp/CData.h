//
// Created by Administrator on 2020/6/15.
//

#ifndef CPLAY_CDATA_H
#define CPLAY_CDATA_H


struct CData {
    unsigned char* data = 0;
    int size = 0;
    void drop();
};


#endif //CPLAY_CDATA_H
