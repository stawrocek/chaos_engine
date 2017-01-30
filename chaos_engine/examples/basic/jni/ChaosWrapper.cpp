#ifndef CHAOS_WRAPPER_HPP
#define CHAOS_WRAPPER_HPP

#include <stdlib.h>
#include <jni.h>
#include <android/log.h>
#include <GLES2/gl2.h>
#include "../basic_app.hpp"

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO,"Chaos", __VA_ARGS__))

extern "C"
{
	BasicApplication app;
	
	JNIEXPORT void JNICALL
	Java_com_chaos_example_basic_RendererWrapper_nativeOnSurfaceCreated(
	JNIEnv* env, jobject obj )
	{
		LOGI( "Chaos_Engine_Basic_Example" );
		app.onCreate();
	}

	JNIEXPORT void JNICALL
	Java_com_chaos_example_basic_RendererWrapper_nativeOnSurfaceChanged(
	JNIEnv* env, jclass clazz, int width, int height )
	{
		LOGI( "nativeOnSurfaceChanged: %i x %i", width, height );
		app.onResize(width, height);
	}

	JNIEXPORT void JNICALL
	Java_com_chaos_example_basic_RendererWrapper_nativeOnDrawFrame( JNIEnv* env, jobject obj )
	{
        //LOGI("nativeOnDrawFrame");
		app.onDraw();
	}
}

#endif //CHAOS_WRAPPER_HPP
