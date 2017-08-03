#version 330 core

in vec2 uvCoords;
out vec4 color;
uniform vec4 uniColor;
uniform sampler2D blendMap;
uniform sampler2D textureBackground;
uniform sampler2D textureR;
uniform sampler2D textureG;
uniform sampler2D textureB;

void main(void){
	vec4 blendColor = texture(blendMap, uvCoords);
	float backAmount = 1.0 - (blendColor.r+blendColor.g+blendColor.b);
	vec2 uv = uvCoords;
	vec4 backColor = texture(textureBackground, uv) * backAmount;
	vec4 colorR = texture(textureR, uv) * blendColor.r;
	vec4 colorG = texture(textureG, uv) * blendColor.g;
	vec4 colorB = texture(textureB, uv) * blendColor.b;
	
	color = backColor + colorR + colorG + colorB;
	//color.w=1.0;
	//color = texture(blendMap, uvCoords);
}