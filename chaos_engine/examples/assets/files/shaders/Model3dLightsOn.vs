#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normals;
layout (location = 2) in vec2 uv;
out vec2 uvCoords;

out vec3 normalVector;
out vec3 fragmentPosition;

uniform mat4 model;
uniform mat4 mx;
uniform mat3 normalMatrix;

void main()
{
    gl_Position = mx * vec4(position, 1.0);
	fragmentPosition = vec3(model * vec4(position, 1.0));
    normalVector = normalMatrix * normals;
    uvCoords = uv;
}