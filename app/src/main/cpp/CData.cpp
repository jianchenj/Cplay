//
// Created by Administrator on 2020/6/15.
//

#include "CData.h"

extern "C" {
#include "libavformat/avformat.h"
}

void CData::drop() {
    if (!data) return;
    av_packet_free((AVPacket **) &data/*指向指针的指针*/);
    data = 0;
    size = 0;
}
