#version 330 core

in vec2 uvCoords;
in vec2 uvBlendCoords;
out vec4 color;
uniform vec4 uniColor;
uniform sampler2D blendMap;
uniform sampler2D textureBackground;
uniform sampler2D textureR;
uniform sampler2D textureG;
uniform sampler2D textureB;

void main(void){
	vec4 blendColor = texture(blendMap, uvBlendCoords);
	float backAmount = 1.0 - (blendColor.r+blendColor.g+blendColor.b);
	vec4 backColor = texture(textureBackground, uvCoords) * backAmount;
	vec4 colorR = texture(textureR, uvCoords) * blendColor.r;
	vec4 colorG = texture(textureG, uvCoords) * blendColor.g;
	vec4 colorB = texture(textureB, uvCoords) * blendColor.b;
	
	color = (backColor + colorR + colorG + colorB) * uniColor;
	//color.w=1.0;
	//color = texture(blendMap, uvCoords);
}