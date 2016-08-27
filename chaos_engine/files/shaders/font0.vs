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
	if(id == 1){
        uv = vec2(minx, maxy);
	}
    if(id == 2){
        uv = vec2(maxx, maxy);
    }
	if(id == 3){
        uv = vec2(maxx, miny);
    }
	if(id == 4){
        uv = vec2(minx, miny);
	}
}

