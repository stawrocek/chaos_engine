#ifndef CHAOS_WRAPPER_HPP
#define CHAOS_WRAPPER_HPP

#include <stdlib.h>
#include <queue>
#include <jni.h>
#include <GLES2/gl2.h>
#include "../app.hpp"
#include "../../include/Logger.hpp"
#include "../../include/InputManager.hpp"
#include "../../include/SceneManager.hpp"

extern "C"
{
	class EGLWindow: public chaos::Window{
		public:
		EGLWindow(chaos::WindowStyle ws)
		:Window(ws)
		{
			setDepthEnabled(true);
			setBlendingEnabled(true);
			ImGui_ImplChaos_Init(this);
		}
		virtual ~EGLWindow(){
			ImGui_ImplChaos_Shutdown();
		}

		void update() override {
			ImGui::Render();
			deltaTimer.restart();
			if(fpsTimer.getTime() >= 1000){
				fpsVal = fpsCtr;
				fpsCtr=0;
				fpsTimer.restart();
			}
		};
		
		void swapBuffers() override {};
		int getWidth() override {return winStyle.width;}
		int getGLDrawableWidth() override {return winStyle.width;}
		int getHeight() override {return winStyle.height;}
		int getGLDrawableHeight() override {return winStyle.height;}
		int getPosX() override {return winStyle.posX;}
		int getPosY() override {return winStyle.posY;}
		void setRelativeMode(GLboolean mode) override {}
		void* getWindowW32Handle() override {return nullptr;}
		GLboolean isFocused() override {return true;}		//To be implemented
		GLvoid showCursor(GLboolean flag) override {}		//hmm...
		const GLchar* getClipboardText(void* clipboardPtr) override {return "to-be-implemented";}
		void setClipboardText(void* clipboardPtr, const char* text) override {}
		void runEvents(chaos::SceneManager* sceneManager) override {
			inputManager->runEvents(sceneManager);
			ImGui_ImplChaos_NewFrame(this);
		}
	};

class AndroidInputManager: public chaos::InputManager{
public:
    virtual void runEvents(chaos::SceneManager* sceneManager) override {
        while(!qEvents.empty()){
            chaos::Event ev = qEvents.front();
			ImGui_ImplChaos_ProcessEvent(&ev, this);
            qEvents.pop();
            if(sceneManager != nullptr){
                sceneManager->deliverEvent(&ev);
            }
            if (ev.type == chaos::Event::TouchDown){
                mTouchDown[ev.touchEvent.buttonCode]=true;
				mousePosX = ev.touchEvent.posX;
				mousePosY = ev.touchEvent.posY;
            }
            else if(ev.type == chaos::Event::TouchUp){
                mTouchDown[ev.touchEvent.buttonCode]=false;
				//mousePosX = -1;
				//mousePosY = -1;
			}
			else if(ev.type == chaos::Event::MouseMotion){
				mousePosX = ev.motionEvent.posX;
				mousePosY = ev.motionEvent.posY;
			}
            else if (ev.type == chaos::Event::KeyDown){
                mKeyDown[ev.keyEvent.keyCode]=true;
            }
            else if (ev.type == chaos::Event::KeyUp){
                mKeyDown[ev.keyEvent.keyCode]=false;
            }
        }
    }
    virtual GLuint getMouseX() override {return mousePosX;}
    virtual GLuint getMouseY() override {return mousePosY;}
    virtual chaos::Event translateEvent(void* nativeEvent) override {
        chaos::Event e;
        e.type = chaos::Event::None;
        return e;
    }
protected:
	GLuint mousePosX=-1, mousePosY=-1;
};

	EGLWindow* window=nullptr;
	ChaosExampleLibraryApp app;
	JNIEXPORT void JNICALL
	Java_com_chaos_example_basic_RendererWrapper_nativeOnSurfaceCreated(
	JNIEnv* env, jobject obj, jstring dataStoragePath )
	{
		if(window == nullptr){
			window = new EGLWindow(chaos::WindowStyle("Chaos - EGL", 0,0,700,700));
			window->inputManager = new AndroidInputManager();
			SHOUT("%s", "created in nativeOnSurfaceCreated");
		}
		app.setWindow(window);
		std::string tmpPath = env->GetStringUTFChars(dataStoragePath, NULL);
		if(tmpPath != "")
			tmpPath+="/";
		chaos::Application::setDataStorageDirectory(tmpPath);
		SHOUT("chos storage_path: %s", chaos::Application::getDataStorageDirectory().c_str());
		app.onCreate();
	}

	JNIEXPORT void JNICALL
	Java_com_chaos_example_basic_RendererWrapper_nativeOnSurfaceChanged(
	JNIEnv* env, jclass clazz, int width, int height )
	{
		SHOUT( "nativeOnSurfaceChanged: %i x %i", width, height );
		if(window==nullptr){
			window = new EGLWindow(chaos::WindowStyle("Chaos - EGL", 0,0,700,700));
            window->inputManager = new AndroidInputManager();
            SHOUT("%s", "created in onSurfaceChanged\n");
		}

		window->setStyle(chaos::WindowStyle("Chaos - EGL", 0,0,width,height));
		app.onResize(width, height);
	}

	JNIEXPORT void JNICALL
	Java_com_chaos_example_basic_RendererWrapper_nativeOnDrawFrame( JNIEnv* env, jobject obj )
	{
		app.onDraw();
	}

    JNIEXPORT void JNICALL
	Java_com_chaos_example_basic_ChaosActivity_nativeOnTouchDown(
	JNIEnv* env, jclass clazz, int x, int y )
	{
		SHOUT("nativeOnTouchDown: %d x %d", x, y);
		chaos::Event ev;
		ev.type = chaos::Event::TouchDown;
        ev.touchEvent.posX = x;
        ev.touchEvent.posY = y;
        ev.touchEvent.buttonCode = chaos::TouchEvent::ButtonLeft;
		window->inputManager->pushEvent(ev);
	}

    JNIEXPORT void JNICALL
	Java_com_chaos_example_basic_ChaosActivity_nativeOnTouchUp(
	JNIEnv* env, jclass clazz, int x, int y )
	{
		SHOUT( "nativeOnTouchDownUp: %d x %d", x, y );
        chaos::Event ev;
		ev.type = chaos::Event::TouchUp;
        ev.touchEvent.posX = x;
        ev.touchEvent.posY = y;
        ev.touchEvent.buttonCode = chaos::TouchEvent::ButtonLeft;
		window->inputManager->pushEvent(ev);
	}

	JNIEXPORT void JNICALL
	Java_com_chaos_example_basic_ChaosActivity_nativeOnMove(
	JNIEnv* env, jclass clazz, int x, int y, int lastX, int lastY)
	{
		SHOUT( "nativeOnMove: (%d x %d), (%d x %d)", x, y, lastX, lastY);
		chaos::Event ev;
		ev.type = chaos::Event::MouseMotion;
        ev.motionEvent.posX = x;
        ev.motionEvent.posY = y;
        ev.motionEvent.relX = x-lastX;
        ev.motionEvent.relY = y-lastY;
		window->inputManager->pushEvent(ev);
	}

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
