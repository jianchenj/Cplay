//
// Created by Administrator on 2020/6/28.
//

#include <android/native_window.h>
#include "CEGL.h"
#include "CLog.h"
#include <EGL/egl.h>

class CCEGL : public CEGL {
public:
    EGLDisplay display = EGL_NO_DISPLAY;
    EGLSurface surface = EGL_NO_SURFACE;
    EGLContext context = EGL_NO_CONTEXT;

    bool Init(void *win) override {
        ANativeWindow *nwin = (ANativeWindow *) win;

        //初始化EGL
        //1. 获取EGLDisplay对象 显示设备
        display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
        if (display == EGL_NO_DISPLAY) {
            CLOGE("eglGetDisplay failed!!");
            return false;
        }
        CLOGI("eglGetDisplay success");

        //3.初始化EGLDisplay
        if (EGL_TRUE != eglInitialize(display, 0, 0)) {
            CLOGE("eglInitialize failed!!");
            return false;
        }
        CLOGI("eglInitialize success");

        //3.获取配置并创建surface
        EGLint configSpec[] = {
                EGL_RED_SIZE, 8,
                EGL_GREEN_SIZE, 8,
                EGL_BLUE_SIZE, 8,
                EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
                EGL_NONE
        };
        EGLConfig config = nullptr;
        EGLint numConfigs = 0;
        if (EGL_TRUE != eglChooseConfig(display, configSpec, &config, 1, &numConfigs)) {
            CLOGE("eglChooseConfig failed!!");
            return false;
        }
        CLOGI("eglChooseConfig success");
        surface = eglCreateWindowSurface(display, config, nwin, nullptr);

        //4.创建并打开EGL上下文
        const EGLint ctxAttr[] = {
                EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE
        };
        context = eglCreateContext(display, config, EGL_NO_CONTEXT, ctxAttr);
        if (context == EGL_NO_CONTEXT) {
            CLOGE("eglCreateContext failed!!");
            return false;
        }
        CLOGI("eglCreateContext success");

        if (EGL_TRUE != eglMakeCurrent(display, surface, surface, context)) {
            CLOGE("eglMakeCurrent failed!!");
            return false;
        }
        CLOGI("eglMakeCurrent success");
        return false;
    }
};

CEGL *CEGL::Get() {
    static CCEGL egl;
    return &egl;
}


