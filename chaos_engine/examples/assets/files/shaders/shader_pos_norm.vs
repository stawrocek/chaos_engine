#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normals;

out vec3 normalVector;
out vec3 fragmentPosition;

uniform mat4 model;
uniform mat4 mx;

void main()
{
	gl_Position = mx * vec4(position, 1.0);
	fragmentPosition = vec3(model * vec4(position, 1.0));
    normalVector = normals;  
}