#version 330 core

// Interpolated values from the vertex shaders
in vec2 UV;

// Ouput data
out vec4 outColor;

//data
uniform vec4 color;
uniform vec4 frontColor;
uniform float frontWidth;

void main(){
	if (UV.x < frontWidth) outColor = frontColor;
	else outColor = color;
}
