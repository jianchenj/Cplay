package com.jchen.cplay;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.view.SurfaceHolder;

public class CPlay extends GLSurfaceView implements SurfaceHolder.Callback {

    public CPlay(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        //初始化 opengl egl 显示
        initView(holder.getSurface());
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int w, int h) {
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
    }

    public native void initView(Object surface);
}
