#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 vecNormal;
layout (location = 2) in vec2 uv;

uniform mat4 mx;

out VS_OUT {
    vec2 uvCoords;
	vec3 vNormal;
} vs_out;

void main()
{
    gl_Position = mx*vec4(position, 1.0f);
    vs_out.uvCoords = uv;
	vs_out.vNormal = vecNormal;
}