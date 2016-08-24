#version 330 core
out vec4 color;

in vec2 uv;
uniform sampler2D tex0;

void main() {
	color = texture(tex0, vec2(uv.x, uv.y));
}

