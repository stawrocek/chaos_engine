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
	JNIEnv* env, jobject obj, jstring dataStoragePath )
	{
		/*jclass activityClass = env->GetObjectClass(obj);
		jmethodID getAppStorageID = env->GetMethodID(activityClass,
									"getApplicationExternalStoragePrefix", "()Ljava/lang/String;");
		if (getAppStorageID == 0){
			LOGI("Function getApplicationExternalStoragePrefix() not found.");
			return;
		}
		jstring result = (jstring)env->CallObjectMethod(obj, getAppStorageID);
		const char* str = env->GetStringUTFChars(result, NULL);
		std::string storageDir=str;
		storageDir += "/";
		chaos::Application::setDataStorageDirectory(storageDir);
		env->ReleaseStringUTFChars(result, str);
		LOGI("data_storage (c++): %s", chaos::Application::getDataStorageDirectory().c_str());*/
		
		std::string tmpPath = env->GetStringUTFChars(dataStoragePath, NULL);
		if(tmpPath != "")
			tmpPath+="/";
		chaos::Application::setDataStorageDirectory(tmpPath);
		LOGI("chos storage_path: %s", chaos::Application::getDataStorageDirectory().c_str());
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

/// C-runtime patch
extern "C"
{
    // used deep inside FreeImage
    void* lfind( const void * key, const void * base, size_t num, size_t width, int (*fncomparison)(const void *, const void * ) )
    {
        char* Ptr = (char*)base;

        for ( size_t i = 0; i != num; i++, Ptr+=width )
        {
            if ( fncomparison( key, Ptr ) == 0 ) return Ptr;
        }

        return NULL;
    }

    // used in libcompress
    int fseeko64(FILE *stream, off64_t offset, int whence)
    {
        return fseek( stream, int( offset & 0xFFFFFFFF ), whence );
    }

    // used in libcompress
    off64_t ftello64(FILE *stream)
    {
        return ftell( stream );
    }
} // extern C

#endif //CHAOS_WRAPPER_HPP
