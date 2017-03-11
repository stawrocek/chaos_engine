
make:
	emcc chaos_examples.cpp app.cpp ../src/VertexArray.cpp ../src/Transform.cpp ../src/InputHandler.cpp ../src/Window.cpp ../src/ShaderProgram.cpp ../src/Shader.cpp ../src/Texture.cpp ../src/Application.cpp -o index.html -std=c++11 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' -O2 --preload-file assets