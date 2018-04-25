#version 330 core

#define MAX_LIGHTS 10

// Data structs
struct myLight {
    vec3 position;

    vec3 ambientComponent;
    vec3 diffuseComponent;
    vec3 specularComponent;
};

struct myMaterial {
    vec3 ambientColor;
    vec3 diffuseColor;
    vec3 specularColor;
};

struct myTexture {
    bool haveAmbientTexture;
    bool haveDiffuseTexture;
    bool haveSpecularTexture;
    bool haveAlphaTexture;
    bool haveBumpTexture;
};

// Interpolated values from the vertex shaders
in vec3 vertexPosition_out;
in vec3 vertexNormal_out;
in vec2 vertexUV_out;

in vec3 normalizedVertexPosition_out;

// Ouput data
layout(location = 0) out vec4 FragColor;

// Buffers
layout (std140) uniform LightBuffer {
    myLight lights[MAX_LIGHTS];
};

layout (std140) uniform MaterialBuffer {
    myMaterial material;
};

layout (std140) uniform TextureBuffer {
    myTexture tex;
};

// Uniforms
uniform int lightAmount;

// Samplers
uniform sampler2D ambientTexture;
uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;
uniform sampler2D alphaTexture;
uniform sampler2D bumpTexture;

// FUNCION QUE CALCULA EL MODELO DE REFLEXION DE PHONG
vec3 Phong(myLight light) {
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;

    // CALCULAR LOS DIFERENTES VECTORES	 
    vec3 s = normalize(light.position - vertexPosition_out);
	vec3 r = reflect(-s, vertexNormal_out);

	// COMPONENTE AMBIENTAL
    if (tex.haveAmbientTexture == true){
        Ambient = light.ambientComponent * texture(ambientTexture, vertexUV_out).rgb;
    } else {
        Ambient = light.ambientComponent * material.ambientColor;
    }
  	
    // COMPONENTE DIFUSA 
    if (tex.haveDiffuseTexture == true){
        Diffuse = light.diffuseComponent * max(dot(s, vertexNormal_out), 0.0) * texture(diffuseTexture, vertexUV_out).rgb;
    } else {
        Diffuse = light.diffuseComponent * max(dot(s, vertexNormal_out), 0.0) * material.diffuseColor;
    }

    // COMPONENTE ESPECULAR  
    if (tex.haveSpecularTexture == true){
        Specular = light.specularComponent * pow(max(dot(r, normalizedVertexPosition_out), 0.0), 1) * texture(specularTexture, vertexUV_out).rgb;
    } else {
        Specular = light.specularComponent * pow(max(dot(r, normalizedVertexPosition_out), 0.0), 1) * material.specularColor;
    }

    return Ambient + Diffuse + Specular;  
} 

void main(){
    // Output color = addition of all the colors of the texture at the specified UV
    vec3 finalColor = vec3(0,0,0);
    for (int i = 0; i < lightAmount; i++){
        finalColor = finalColor + Phong(lights[i]);
    }
    FragColor = vec4(finalColor, 1);
}