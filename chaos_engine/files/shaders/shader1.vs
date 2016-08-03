#version 330 core
layout (location = 0) in vec3 position;
layout (location = 2) in vec2 uv;
out vec2 uvCoords;

uniform mat4 mx;

void main()
{
	gl_Position = mx*vec4(position, 1.0);
	uvCoords = uv;
}