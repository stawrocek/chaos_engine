#version 330 core

layout (location = 0) in vec3 position;

uniform mat4 mx;

void main()
{
	gl_Position = mx*vec4(position, 1.0);
}