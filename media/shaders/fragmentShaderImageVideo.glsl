#version 330 core

uniform sampler2D imageTexture;

in vec2 UV;

out vec4 fragColor;

void main() {
	fragColor = texture(imageTexture, UV);
}