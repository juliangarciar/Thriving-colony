#version 450 core

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

// Ouput data
layout(location = 0) out vec4 FragColor;

// Buffers
layout (std140) uniform LightBuffer {
    myLight lights[1];
};

layout (std140) uniform MaterialBuffer {
    myMaterial material;
};

layout (std140) uniform TextureBuffer {
    myTexture tex;
};

// Samplers
uniform sampler2D ambientTexture;
uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;
uniform sampler2D alphaTexture;
uniform sampler2D bumpTexture;

// FUNCION QUE CALCULA EL MODELO DE REFLEXION DE PHONG
vec3 Phong() {
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;

    // CALCULAR LOS DIFERENTES VECTORES	 
	vec3 n = normalize(vertexNormal_out);
    vec3 s = normalize(lights[0].position - vertexPosition_out);
	vec3 v = normalize(-vertexPosition_out);
	vec3 r = reflect(-s, n);

	// COMPONENTE AMBIENTAL
    if (tex.haveAmbientTexture == true){
        Ambient = lights[0].ambientComponent * (material.ambientColor + texture(ambientTexture, vertexUV_out).rgb);
    } else {
        Ambient = lights[0].ambientComponent * material.ambientColor;
    }
  	
    // COMPONENTE DIFUSA 
    if (tex.haveDiffuseTexture == true){
        Diffuse = lights[0].diffuseComponent * max(dot(s, n), 0.0) * (material.diffuseColor + texture(diffuseTexture, vertexUV_out).rgb);
    } else {
        Diffuse = lights[0].diffuseComponent * max(dot(s, n), 0.0) * material.diffuseColor;
    }

    // COMPONENTE ESPECULAR  
    if (tex.haveSpecularTexture == true){
        Specular = lights[0].specularComponent * pow(max(dot(r, v), 0.0), 1) * (material.specularColor + texture(specularTexture, vertexUV_out).rgb);
    } else {
        Specular = lights[0].specularComponent * pow(max(dot(r, v), 0.0), 1) * material.specularColor;
    }

    return Ambient + Diffuse + Specular;  
} 

void main(){
    // Output color = color of the texture at the specified UV
    FragColor = vec4(Phong(), 1);
}