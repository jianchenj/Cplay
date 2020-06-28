#include <jni.h>
#include <string>

#include "FFDemux.h"
#include "CLog.h"
#include "IDecode.h"
#include "FFDecode.h"
#include "CEGL.h"
#include <android/native_window_jni.h>
#include <android/native_window.h>

class TestObs : public IObserver {
public:
    void Update(CData data) {
        //CLOGI("TestObs Update data size is %d", data.size );
    }
};

extern "C" JNIEXPORT jstring JNICALL
Java_com_jchen_cplay_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";

    ///////////////////////////////////////////////////////////////////////////////////////
    TestObs *tobs = new TestObs();
    // 测试用代码
    IDemux *de = new FFDemux();
    //de->AddObs(tobs);
    de->Open("/sdcard/DCIM/Camera/input.mp4");
    //de->Open("/sdcard/DCIM/Camera/v1080.mp4");


    IDecode *vDecode = new FFDecode();
    vDecode->Open(de->GetVPara());
    de->AddObs(vDecode);


    IDecode *aDecode = new FFDecode();
    aDecode->Open(de->GetAPara());
    de->AddObs(aDecode);

    de->Start();//开始解封装线程
    //开始解码线程
    vDecode->Start();
    aDecode->Start();


    //CSleep(3000);
    //de->Stop();
    ////////////////////////////////////////////////////////////////////////////////////////
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT void JNICALL
Java_com_jchen_cplay_CPlay_initView(JNIEnv *env, jobject thiz, jobject surface) {
    ANativeWindow *win = ANativeWindow_fromSurface(env,surface);
    CEGL::Get()->Init(win);
}