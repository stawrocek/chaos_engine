#version 330 core

in vec2 uvCoords;
out vec4 color;
uniform vec4 uniColor;

uniform sampler2D reflectionTexture;
uniform sampler2D refractionTexture;

void main(void){
	vec4 reflectColor = texture(reflectionTexture, uvCoords);
	vec4 refractColor = texture(refractionTexture, uvCoords);
	color = mix(reflectColor, refractColor, 0.5);
}