package com.chaos.example.basic;
import android.app.Activity;
import android.os.Bundle;
import android.opengl.GLSurfaceView;
import android.widget.Toast;
import android.util.Log;
import java.io.IOException;
import java.io.BufferedReader;
import java.io.FileWriter;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.FileOutputStream;
import java.io.InputStreamReader;
import android.os.Environment;
import java.io.File;
import java.io.IOException;
import android.view.MotionEvent;
import android.view.View;

public class ChaosActivity extends Activity
{
	private GLSurfaceView glSurfaceView;
    private boolean rendererSet=false;
    private String DEBUG_TAG="ChaosDbg";
    float lastX, lastY;
	static{
		System.loadLibrary("ChaosWrapper");
	}
	@Override protected void onCreate(Bundle bundle){
		super.onCreate(bundle);
		listAssetFiles("files");

		glSurfaceView = new GLSurfaceView(this);
		glSurfaceView.setEGLContextClientVersion(2);
		//glSurfaceView.setEGLConfigChooser(8, 8, 8, 8, 16, 0);
		glSurfaceView.setRenderer(new RendererWrapper());
		glSurfaceView.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event){
                if(event.getAction() == MotionEvent.ACTION_DOWN){
                    nativeOnTouchDown((int)event.getX(), (int)event.getY());
                    lastX = event.getX();
                    lastY = event.getY();
                }
                else if(event.getAction() == MotionEvent.ACTION_MOVE){
                    nativeOnMove((int)event.getX(), (int)event.getY(), (int)lastX, (int)lastY);
                    lastX = event.getX();
                    lastY = event.getY();
                }
                else if(event.getAction() == MotionEvent.ACTION_UP){
                    nativeOnTouchUp((int)event.getX(), (int)event.getY());
                }
                return true;
            }
        });
		rendererSet=true;
		Toast.makeText(this, "Hello",Toast.LENGTH_LONG).show();
		setContentView(glSurfaceView);
	}

    public native void nativeOnTouchDown(int x, int y);
    public native void nativeOnTouchUp(int x, int y);
    public native void nativeOnMove(int x, int y, int _lastX, int _lastY);

	String getApplicationExternalStoragePrefix()
	{
		String Suffix = "/external_sd/Android/data/";
		return Environment.getExternalStorageDirectory().getPath() +
			Suffix + getApplication().getPackageName();
	}

	private boolean listAssetFiles(String path) {
		String [] list;
		try {
			list = getAssets().list(path);
			if(list.length == 0){
				Log.w(DEBUG_TAG, "Found new file: " + path);
				copyFileToSDCard(path);
			}
			for(String file: list){
				if(path!="")
					listAssetFiles(path + "/" + file);
				else
					listAssetFiles(file);
			}
		} catch (IOException e) {
			return false;
		}
		return true;
	}

	private void copyFileToSDCard(String fpath){
		InputStream in = null;
		OutputStream out = null;
		String sdpath = getApplicationExternalStoragePrefix()+"/"+fpath;
		try{
			in = getAssets().open(fpath);
			File outFile = new File(sdpath);
			//Log.w(DEBUG_TAG, sdpath);
			outFile.getParentFile().mkdirs();
			outFile.createNewFile();
			out = new FileOutputStream(outFile);
			copyFiles(in, out);
		} catch (IOException e){
			Log.e(DEBUG_TAG, "Failed to copy asset file: " + fpath, e);
		}
		finally {
            if (in != null) {
                try {
                    in.close();
                } catch (IOException e) {
                    // NOOP
                }
            }
            if (out != null) {
                try {
                    out.close();
                } catch (IOException e) {
                    // NOOP
                }
            }
        }
	}

	private void copyFiles(InputStream in, OutputStream out){
		try{
			byte[] buffer = new byte[4096];
			int len;
			while ((len = in.read(buffer)) != -1) {
				out.write(buffer, 0, len);
			}
		}
		catch (Exception e){

		}
	}
};
