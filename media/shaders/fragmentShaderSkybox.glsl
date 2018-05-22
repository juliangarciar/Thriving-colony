#version 330 core

out vec4 FragColor;

in vec3 UV;

uniform samplerCube skybox;

void main() {    
    FragColor = vec4(texture(skybox, UV).rgb, 1);
}