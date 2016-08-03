#version 330 core
out vec4 color;

in vec2 uvCoords;

uniform sampler2D tex0;
uniform vec4 ourColor;

void main(){
	color = mix(texture(tex0, uvCoords), ourColor, 0.2);
}