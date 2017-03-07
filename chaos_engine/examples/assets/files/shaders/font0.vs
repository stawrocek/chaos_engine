#version 330 core
layout (location = 0) in vec3 position;
layout (location = 3) in float data;

uniform mat4 mvp;
uniform float minx;
uniform float maxx;
uniform float miny;
uniform float maxy;

out vec2 uv;

void main() {
    gl_Position = mvp * vec4(position.x, position.y, position.z, 1.0);
	if(abs(data-1.0) < 0.01){
        uv = vec2(minx, maxy);
	}
    if(abs(data-2.0) < 0.01){
        uv = vec2(maxx, maxy);
    }
	if(abs(data-3.0) < 0.01){
        uv = vec2(maxx, miny);
    }
	if(abs(data-4.0) < 0.01){
        uv = vec2(minx, miny);
	}
}

