#version 330 core
layout (location = 0) in vec4 pos;

uniform mat4 mvp;
uniform float minx;
uniform float maxx;
uniform float miny;
uniform float maxy;

out vec2 uv;

void main() {
    gl_Position = mvp * vec4(pos.x, pos.y, pos.z, 1.0);
	if(pos.w == 1){
        uv = vec2(minx, maxy);
	}
    if(pos.w == 2){
        uv = vec2(maxx, maxy);
    }
	if(pos.w == 3){
        uv = vec2(maxx, miny);
    }
	if(pos.w == 4){
        uv = vec2(minx, miny);
	}
}

