package com.chaos.example.basic;

import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;
import android.util.Log;
import android.os.Environment;

public class RendererWrapper implements GLSurfaceView.Renderer {
    
	String getApplicationExternalStoragePrefix()
	{
		String Suffix = "/external_sd/Android/data/";
		return Environment.getExternalStorageDirectory().getPath() +
			Suffix + getClass().getPackage().getName();
	}
	
	
	@Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        nativeOnSurfaceChanged(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
		if(drawCounter==0){
			drawCounter++;
			nativeOnSurfaceCreated(getApplicationExternalStoragePrefix());
		}
        nativeOnDrawFrame();
    }

    public native void nativeOnSurfaceCreated(String strDataPath);
    public native void nativeOnSurfaceChanged(int w, int h);
    public native void nativeOnDrawFrame();
	
	private static int drawCounter = 0;
}
