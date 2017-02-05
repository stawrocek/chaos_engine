#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 3) in float id;

uniform mat4 mvp;
uniform float minx;
uniform float maxx;
uniform float miny;
uniform float maxy;

out vec2 uv;

void main() {
    gl_Position = mvp * vec4(pos.x, pos.y, pos.z, 1.0);
	if(abs(id-1.0) < 0.01){
        uv = vec2(minx, maxy);
	}
    if(abs(id-2.0) < 0.01){
        uv = vec2(maxx, maxy);
    }
	if(abs(id-3.0) < 0.01){
        uv = vec2(maxx, miny);
    }
	if(abs(id-4.0) < 0.01){
        uv = vec2(minx, miny);
	}
}

