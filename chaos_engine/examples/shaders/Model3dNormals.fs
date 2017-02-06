#version 330 core
out vec4 color;

uniform vec4 uniColor;

in vec4 outColor;

void main()
{
    color = outColor*uniColor;
}