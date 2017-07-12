# -*- Makefile -*-

#target:dependencies
#	action

CC=g++
CFLAGS=-std=c++11 -O2 -Wall
HEADERS=-I external_libs/include
LIBS=-lglu32 -lmingw32 

GLEW_LIB=external_libs/lib/glew32s.lib
FREE_IMAGE_LIB=external_libs/lib/FreeImage.lib
OPENGL_LIB=external_libs/lib/libopengl32.a

#SOURCES=src/MeshPrefab.cpp src/Shader.cpp src/ShaderProgram.cpp src/Texture.cpp \
#src/Transform.cpp src/VertexArray.cpp src/Window.cpp
#OBJECTS=build/InputHandler.o build/MeshPrefab.o build/Shader.o build/ShaderProgram.o build/Texture.o \
#build/Timer.o build/Transform.o build/VertexArray.o build/Window.o

SOURCES=src/Application.cpp src/BitmapFont.cpp src/BitmapFontSprite.cpp \
src/Camera.cpp src/GameObject.cpp \
src/InputManager.cpp src/LightCaster.cpp src/Material.cpp \
src/MeshPrefab.cpp src/Model.cpp src/Primitives.cpp \
src/Renderer.cpp src/Resource.cpp src/ResourceManager.cpp \
src/Scene.cpp src/SceneManager.cpp src/Shader.cpp \
src/ShaderProgram.cpp \
src/Sprite.cpp \
src/Texture.cpp src/Timer.cpp src/Transform.cpp \
src/VertexArray.cpp src/Window.cpp
#src/ImGUI_Impl_Chaos.cpp \
#include/imgui/imgui.cpp include/imgui/imgui_draw.cpp

OBJECTS=build/Application.o build/BitmapFont.o build/BitmapFontSprite.o \
build/Camera.o build/CubeMap.o build/FBO.cpp build/GameObject.o \
build/InputManager.o build/LightCaster.o build/Material.o \
build/MeshPrefab.o build/Model.o build/Primitives.o \
build/Renderer.o build/Resource.o build/ResourceManager.o \
build/Scene.o build/SceneManager.o build/Shader.o \
build/ShaderProgram.o build/Skybox.o \
build/Sprite.o \
build/Texture.o build/Timer.o build/Transform.o \
build/VertexArray.o build/Window.o
#build/ImGUI_Impl_Chaos.o \
#build/imgui.o build/imgui_draw.o

EXEC=chaos.exe
MAIN=examples/tech_demo.cpp

Chaos: $(OBJECTS)
	$(CC) -shared -o build/chaosengine.dll $(HEADERS) $(OBJECTS) $(LIBS) -Wl,--out-implib,build/libchaosengine.lib $(GLEW_LIB) $(OPENGL_LIB) $(FREE_IMAGE_LIB)

build/Application.o: src/Application.cpp include/Application.hpp
	$(CC) -c -DDLL_EXPORT src/Application.cpp $(HEADERS) $(CFLAGS) -o build/Application.o

build/BitmapFont.o: src/BitmapFont.cpp include/BitmapFont.hpp
	$(CC) -c -DDLL_EXPORT src/BitmapFont.cpp $(HEADERS) $(CFLAGS) -o build/BitmapFont.o	

build/BitmapFontSprite.o: src/BitmapFontSprite.cpp include/BitmapFontSprite.hpp
	$(CC) -c -DDLL_EXPORT src/BitmapFontSprite.cpp $(HEADERS) $(CFLAGS) -o build/BitmapFontSprite.o	

build/Camera.o: src/Camera.cpp include/Camera.hpp
	$(CC) -c -DDLL_EXPORT src/Camera.cpp $(HEADERS) $(CFLAGS) -o build/Camera.o	

build/CubeMap.o: src/CubeMap.cpp include/CubeMap.hpp
	$(CC) -c -DDLL_EXPORT src/CubeMap.cpp $(HEADERS) $(CFLAGS) -o build/CubeMap.o	

build/FBO.o: src/FBO.cpp include/FBO.hpp
	$(CC) -c -DDLL_EXPORT src/FBO.cpp $(HEADERS) $(CFLAGS) -o build/FBO.o
	
build/GameObject.o: src/GameObject.cpp include/GameObject.hpp
	$(CC) -c -DDLL_EXPORT src/GameObject.cpp $(HEADERS) $(CFLAGS) -o build/GameObject.o	

build/ImGUI_Impl_Chaos.o: src/ImGUI_Impl_Chaos.cpp include/ImGUI_Impl_Chaos.hpp
	$(CC) -c -DDLL_EXPORT src/ImGUI_Impl_Chaos.cpp $(HEADERS) $(CFLAGS) -o build/ImGUI_Impl_Chaos.o	
	
build/InputManager.o: src/InputManager.cpp include/InputManager.hpp
	$(CC) -c -DDLL_EXPORT src/InputManager.cpp $(HEADERS) $(CFLAGS) -o build/InputManager.o	

build/LightCaster.o: src/LightCaster.cpp include/LightCaster.hpp
	$(CC) -c -DDLL_EXPORT src/LightCaster.cpp $(HEADERS) $(CFLAGS) -o build/LightCaster.o	

build/Material.o: src/Material.cpp include/Material.hpp
	$(CC) -c -DDLL_EXPORT src/Material.cpp $(HEADERS) $(CFLAGS) -o build/Material.o	
		
build/MeshPrefab.o: src/MeshPrefab.cpp include/MeshPrefab.hpp
	$(CC) -c -DDLL_EXPORT src/MeshPrefab.cpp $(HEADERS) $(CFLAGS) -o build/MeshPrefab.o

build/Model.o: src/Model.cpp include/Model.hpp
	$(CC) -c -DDLL_EXPORT src/Model.cpp $(HEADERS) $(CFLAGS) -o build/Model.o	
	
build/Primitives.o: src/Primitives.cpp include/Primitives.hpp
	$(CC) -c -DDLL_EXPORT src/Primitives.cpp $(HEADERS) $(CFLAGS) -o build/Primitives.o	

build/Renderer.o: src/Renderer.cpp include/Renderer.hpp
	$(CC) -c -DDLL_EXPORT src/Renderer.cpp $(HEADERS) $(CFLAGS) -o build/Renderer.o	

build/Resource.o: src/Resource.cpp include/Resource.hpp
	$(CC) -c -DDLL_EXPORT src/Resource.cpp $(HEADERS) $(CFLAGS) -o build/Resource.o	

build/ResourceManager.o: src/ResourceManager.cpp include/ResourceManager.hpp
	$(CC) -c -DDLL_EXPORT src/ResourceManager.cpp $(HEADERS) $(CFLAGS) -o build/ResourceManager.o	

build/Scene.o: src/Scene.cpp include/Scene.hpp
	$(CC) -c -DDLL_EXPORT src/Scene.cpp $(HEADERS) $(CFLAGS) -o build/Scene.o	
	
build/SceneManager.o: src/SceneManager.cpp include/SceneManager.hpp
	$(CC) -c -DDLL_EXPORT src/SceneManager.cpp $(HEADERS) $(CFLAGS) -o build/SceneManager.o	
	
build/Shader.o: src/Shader.cpp include/Shader.hpp
	$(CC) -c -DDLL_EXPORT src/Shader.cpp $(HEADERS) $(CFLAGS) -o build/Shader.o
	
build/ShaderProgram.o: src/ShaderProgram.cpp include/ShaderProgram.hpp
	$(CC) -c -DDLL_EXPORT src/ShaderProgram.cpp $(HEADERS) $(CFLAGS) -o build/ShaderProgram.o

build/Skybox.o: src/Skybox.cpp include/Skybox.hpp
	$(CC) -c -DDLL_EXPORT src/Skybox.cpp $(HEADERS) $(CFLAGS) -o build/Skybox.o
	
build/Sprite.o: src/Sprite.cpp include/Sprite.hpp
	$(CC) -c -DDLL_EXPORT src/Sprite.cpp $(HEADERS) $(CFLAGS) -o build/Sprite.o		
	
build/Texture.o: src/Texture.cpp include/Texture.hpp
	$(CC) -c -DDLL_EXPORT src/Texture.cpp $(HEADERS)  $(CFLAGS) -o build/Texture.o
	
build/Timer.o: src/Timer.cpp include/Timer.hpp
	$(CC) -c -DDLL_EXPORT src/Timer.cpp $(HEADERS)  $(CFLAGS) -o build/Timer.o 

build/Transform.o: src/Transform.cpp include/Transform.hpp
	$(CC) -c -DDLL_EXPORT src/Transform.cpp $(HEADERS) $(CFLAGS) -o build/Transform.o
	
build/VertexArray.o: src/VertexArray.cpp include/VertexArray.hpp
	$(CC) -c -DDLL_EXPORT src/VertexArray.cpp $(HEADERS) $(CFLAGS) -o build/VertexArray.o

build/Window.o: src/Window.cpp include/Window.hpp
	$(CC) -c -DDLL_EXPORT src/Window.cpp $(HEADERS) $(CFLAGS) -o build/Window.o

#imgui
#build/imgui.o: include/imgui/imgui.cpp include/imgui/imgui.h
#	$(CC) -c -DIMGUI_API -DDLL_EXPORT include/imgui/imgui.cpp $(HEADERS) $(CFLAGS) -o build/imgui.o

#build/imgui_draw.o: include/imgui/imgui_draw.cpp
#	$(CC) -c -DIMGUI_API -DDLL_EXPORT include/imgui/imgui_draw.cpp $(HEADERS) $(CFLAGS) -o build/imgui_draw.o
