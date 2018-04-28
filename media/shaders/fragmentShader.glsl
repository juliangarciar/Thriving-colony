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
uniform sampler2D textureAmbient;
uniform sampler2D textureDiffuse;
uniform sampler2D textureSpecular;
uniform sampler2D textureAlpha;
uniform sampler2D textureBump;

// FUNCION QUE CALCULA EL MODELO DE REFLEXION DE PHONG
vec3 Phong(myLight light, vec3 ambientColor, vec3 diffuseColor, vec3 specularColor) {
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;

    // CALCULAR LOS DIFERENTES VECTORES	 
    vec3 s = normalize(light.position - vertexPosition_out);
	vec3 r = reflect(-s, vertexNormal_out);

	// COMPONENTE AMBIENTAL
    Ambient = light.ambientComponent * ambientColor;
  	
    // COMPONENTE DIFUSA 
    Diffuse = light.diffuseComponent * max(dot(s, vertexNormal_out), 0.0) * diffuseColor;

    // COMPONENTE ESPECULAR
    Specular = light.specularComponent * pow(max(dot(r, normalizedVertexPosition_out), 0.0), 1) * specularColor;

    return Ambient + Diffuse + Specular;  
} 

void main(){
    vec3 ambientColor;
    vec3 diffuseColor;
    vec3 specularColor;

	//Color ambiental
    if (tex.haveAmbientTexture == true){
        ambientColor = texture(textureAmbient, vertexUV_out).rgb * material.ambientColor;
    } else {
        ambientColor = material.ambientColor;
    }
  	
    //Color difusa
    if (tex.haveDiffuseTexture == true){
        diffuseColor = texture(textureDiffuse, vertexUV_out).rgb * material.diffuseColor;
		//Also multiply diffuse and ambient
		ambientColor = texture(textureDiffuse, vertexUV_out).rgb * ambientColor;
    } else {
        diffuseColor = material.diffuseColor;
    }

	//Color especular
    if (tex.haveSpecularTexture == true){
        specularColor = texture(textureSpecular, vertexUV_out).rgb * material.specularColor;
    } else {
        specularColor = material.specularColor;
    }

    // Output color = addition of all the colors of the texture at the specified UV
    vec3 finalColor = vec3(0,0,0);
    for (int i = 0; i < lightAmount; i++){
        finalColor = finalColor + Phong(lights[i], ambientColor, diffuseColor, specularColor);
    }

    FragColor.rgb = finalColor;

	if (tex.haveAlphaTexture == true){
		FragColor.a = texture(textureAlpha, vertexUV_out).r;
	} else {
		FragColor.a = 1;
	}
}