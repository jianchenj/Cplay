//
// Created by Administrator on 2020/6/28.
//

#ifndef CPLAY_CEGL_H
#define CPLAY_CEGL_H


class CEGL {
public:
    virtual bool Init(void *win) = 0;
    static CEGL *Get();

protected:
    CEGL(){}
};


#endif //CPLAY_CEGL_H
