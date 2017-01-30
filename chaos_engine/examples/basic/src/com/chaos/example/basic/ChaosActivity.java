package com.chaos.example.basic;
import android.app.Activity;
import android.os.Bundle;
import android.opengl.GLSurfaceView;
import android.widget.Toast;

public class ChaosActivity extends Activity
{
	private GLSurfaceView glSurfaceView;
    private boolean rendererSet=false;
	static{
		System.loadLibrary("ChaosWrapper");
	}
	@Override protected void onCreate(Bundle bundle){
		super.onCreate(bundle);
		glSurfaceView = new GLSurfaceView(this);
		glSurfaceView.setEGLContextClientVersion(2);
		glSurfaceView.setRenderer(new RendererWrapper());
		rendererSet=true;
		Toast.makeText(this, "Hello",Toast.LENGTH_LONG).show();
		setContentView(glSurfaceView);
	}
};
