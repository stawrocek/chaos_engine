# -*- Makefile -*-

#target:dependencies
#	action

CC=g++
CFLAGS=-std=c++11 -O2 -Wall
HEADERS=-I external_libs/include
LIBS=-lglu32 -lmingw32 -lSDL2main -lSDL2

SDL_PATH=-L external_libs/lib/

GLEW_LIB=external_libs/lib/glew32s.lib
FREE_IMAGE_LIB=external_libs/lib/FreeImage.lib
OPENGL_LIB=external_libs/lib/libopengl32.a

SOURCES=src/InputHandler.cpp src/MeshPrefab.cpp src/Shader.cpp src/ShaderProgram.cpp src/Texture.cpp \
src/Transform.cpp src/VertexArray.cpp src/Window.cpp
OBJECTS=build/InputHandler.o build/MeshPrefab.o build/Shader.o build/ShaderProgram.o build/Texture.o \
build/Transform.o build/VertexArray.o build/Window.o

EXEC=chaos.exe
MAIN=examples/tech_demo.cpp

Chaos: $(OBJECTS)
	$(CC) -shared -o build/chaosengine.dll $(HEADERS) $(OBJECTS) $(SDL_PATH) $(LIBS) -Wl,--out-implib,build/libchaosengine.lib $(GLEW_LIB) $(OPENGL_LIB) $(FREE_IMAGE_LIB)
	
ObjectLoaderExample: $(OBJECTS) build/tech_demo.o
	$(CC) -DDEVELOPMENT_MODE $(SDL_PATH) -o build/chaos.exe $(OBJECTS) build/tech_demo.o $(LIBS) $(GLEW_LIB) $(OPENGL_LIB) $(FREE_IMAGE_LIB) 

build/tech_demo.o: examples/tech_demo.cpp
	$(CC) -c -DDLL_EXPORT examples/tech_demo.cpp $(HEADERS) $(CFLAGS) -o build/tech_demo.o
	
build/InputHandler.o: src/InputHandler.cpp include/InputHandler.hpp
	$(CC) -c -DDLL_EXPORT src/InputHandler.cpp $(HEADERS) $(CFLAGS) -o build/InputHandler.o
	
build/MeshPrefab.o: src/MeshPrefab.cpp include/MeshPrefab.hpp
	$(CC) -c -DDLL_EXPORT src/MeshPrefab.cpp $(HEADERS) $(CFLAGS) -o build/MeshPrefab.o

build/Shader.o: src/Shader.cpp include/Shader.hpp
	$(CC) -c -DDLL_EXPORT src/Shader.cpp $(HEADERS) $(CFLAGS) -o build/Shader.o
	
build/ShaderProgram.o: src/ShaderProgram.cpp include/ShaderProgram.hpp
	$(CC) -c -DDLL_EXPORT src/ShaderProgram.cpp $(HEADERS) $(CFLAGS) -o build/ShaderProgram.o
	
build/Texture.o: src/Texture.cpp include/Texture.hpp
	$(CC) -c -DDLL_EXPORT src/Texture.cpp $(HEADERS)  $(CFLAGS) -o build/Texture.o

build/Transform.o: src/Transform.cpp include/Transform.hpp
	$(CC) -c -DDLL_EXPORT src/Transform.cpp $(HEADERS) $(CFLAGS) -o build/Transform.o
	
build/VertexArray.o: src/VertexArray.cpp include/VertexArray.hpp
	$(CC) -c -DDLL_EXPORT src/VertexArray.cpp $(HEADERS) $(CFLAGS) -o build/VertexArray.o

build/Window.o: src/Window.cpp include/Window.hpp
	$(CC) -c -DDLL_EXPORT src/Window.cpp $(HEADERS) $(CFLAGS) -o build/Window.o
