//
// Created by Administrator on 2020/6/15.
//

#ifndef CPLAY_CLOG_H
#define CPLAY_CLOG_H


class CLog {

};

#ifdef ANDROID //如果是安卓平台

#include <android/log.h>

#define CLOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, "CPlay", __VA_ARGS__)
#define CLOGI(...)  __android_log_print(ANDROID_LOG_INFO, "CPlay", __VA_ARGS__)
#define CLOGE(...)  __android_log_print(ANDROID_LOG_ERROR, "CPlay", __VA_ARGS__)
#else

#endif

#endif //CPLAY_CLOG_H
