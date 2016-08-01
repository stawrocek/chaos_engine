#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
out vec3 ourColor;

uniform mat4 mx;

void main()
{
	gl_Position = mx*vec4(position, 1.0);
	ourColor = color;
}