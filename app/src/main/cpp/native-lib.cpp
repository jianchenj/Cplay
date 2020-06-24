#include <jni.h>
#include <string>

#include "FFDemux.h"
#include "CLog.h"
#include "IDecode.h"
#include "FFDecode.h"

class TestObs:public IObserver {
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
    de->AddObs(tobs);
    de->Open("/sdcard/DCIM/Camera/input.mp4");
    IDecode *vDecode = new FFDecode();
    vDecode->Open(de->GetPara());
    de->Start();
    CSleep(3000);
    de->Stop();
    ////////////////////////////////////////////////////////////////////////////////////////
    return env->NewStringUTF(hello.c_str());
}