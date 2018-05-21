#version 330 core

uniform sampler2D videoTexture;

in vec2 UV;

out vec4 fragColor;

void main() {
	fragColor = vec4(texture(videoTexture, UV).rgb, 1);
}