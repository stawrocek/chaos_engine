
make:
	emcc chaos_examples.cpp app.cpp ../src/VertexArray.cpp ../src/Transform.cpp ../src/InputHandler.cpp ../src/Window.cpp ../src/ShaderProgram.cpp ../src/Shader.cpp ../src/Application.cpp -o index.html -std=c++11 -s USE_SDL=2 -O2 --preload-file assets