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

public class ChaosActivity extends Activity
{
	private GLSurfaceView glSurfaceView;
    private boolean rendererSet=false;
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
		rendererSet=true;
		Toast.makeText(this, "Hello",Toast.LENGTH_LONG).show();
		setContentView(glSurfaceView);
	}
	
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
				Log.w("Chaos", "Found new file: " + path);
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
			out = new FileOutputStream(outFile);
			copyFiles(in, out);
		} catch (IOException e){
			Log.e("Chaos", "Failed to copy asset file: " + fpath, e);
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
	
	/*private void writeFile(String fpath){
		final InputStream in;
		try{
			in = getAssets().open(fpath);
			BufferedReader r = new BufferedReader(new InputStreamReader(in));
			StringBuilder total = new StringBuilder();
			String line;
			while ((line = r.readLine()) != null) {
				total.append(line).append('\n');
			}
			String sdpath = getApplicationExternalStoragePrefix()+"/"+fpath;
			File f = new File(sdpath);
			if(new File(f.getParent()).isDirectory()) {
				//Log.w("Chaos", "directory exists");
			}
			else{
				//Log.w("Chaos", "directory doesn't exists");
				f.getParentFile().mkdirs();
				//Log.w("Chaos", "created dir: " + f.getParent());
				f.createNewFile();
			}
			FileWriter writer = new FileWriter(sdpath); 
			writer.write(total.toString()); 
			writer.flush();
			writer.close();
			//Log.w("Chaos", "file " + fpath + " contents:\n" + total.toString());
		}
		catch (IOException e){
			Log.w("Chaos", "IOException2");
			Log.w("Chaos", e.toString());
			Log.w("Chaos", e.getMessage());
		}
	}*/
};
