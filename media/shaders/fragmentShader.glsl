#version 330 core

#define MAX_LIGHTS 10

// Data structs
struct myLight {
    vec4 position;
    vec4 intensity;

	float ambientCoeficient;
	float attenuationCoeficient;
};

struct myMaterial {
    vec4 ambientColor;
    vec4 diffuseColor;
    vec4 specularColor;

	float shininess;
};

struct myTexture {
    int haveDiffuseTexture;
    int haveAmbientOclusionsTexture;
    int haveSpecularTexture;
    int haveAlphaTexture;
    int haveBumpTexture;
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
uniform vec3 cameraPosition;

// Samplers
uniform sampler2D textureDiffuse;
uniform sampler2D textureOclusions;
uniform sampler2D textureSpecular;
uniform sampler2D textureAlpha;
uniform sampler2D textureBump;

// FUNCION QUE CALCULA EL MODELO DE REFLEXION DE PHONG
vec3 Phong(myLight light, vec3 surfaceColor, vec3 specularColor) {
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;

    // Realizar diferentes calculos
	vec3 dist = light.position.xyz - vertexPosition_out; //3D distance
	float d = sqrt(pow(dist.x, 2) + pow(dist.y, 2) + pow(dist.z, 2)); //1D Distance

    vec3 surfaceToLight = normalize(dist);
    vec3 surfaceToCamera = normalize(cameraPosition - vertexPosition_out);

	// COMPONENTE AMBIENTAL
    Ambient = light.intensity.rgb * surfaceColor * light.ambientCoeficient;
  	
    // COMPONENTE DIFUSA
	float diffuseCoefficient = max(0.0, dot(vertexNormal_out, surfaceToLight));
    Diffuse = light.intensity.rgb * surfaceColor * diffuseCoefficient;

    // COMPONENTE ESPECULAR
	float specularCoefficient = 0.0;
	if (diffuseCoefficient > 0.0) {
		specularCoefficient = pow(max(0.0, dot(surfaceToCamera, reflect(-surfaceToLight, vertexNormal_out))), material.shininess);
	}
    Specular = light.intensity.rgb * specularColor * specularCoefficient;

	float attenuation = 1.0 / (1.0 + light.attenuationCoeficient * pow(d, 2)); //Attenuation
    return Ambient + (Diffuse + Specular) * attenuation;  
} 

void main(){
    vec4 surfaceColor;
    vec4 specularColor;
  	
    //Color difusa
    if (tex.haveDiffuseTexture == 1){
        surfaceColor = texture(textureDiffuse, vertexUV_out) * material.diffuseColor;
    } else {
        surfaceColor = material.diffuseColor;
    }

	//Color oclusiones ambientales
    if (tex.haveAmbientOclusionsTexture == 1){
        surfaceColor = surfaceColor * (texture(textureOclusions, vertexUV_out) * material.ambientColor);
    } else {
        surfaceColor = surfaceColor * material.ambientColor;
    }

	//Color especular
    if (tex.haveSpecularTexture == 1){
        specularColor = texture(textureSpecular, vertexUV_out) * material.specularColor;
    } else {
        specularColor = material.specularColor;
    }

    // Output color = addition of all the colors of the texture at the specified UV
    vec4 finalColor = vec4(0,0,0,0);
    for (int i = 0; i < lightAmount; i++){
        finalColor.rgb = finalColor.rgb + Phong(lights[i], surfaceColor.rgb, specularColor.rgb);
    }

	if (tex.haveAlphaTexture == 1){
		finalColor.a = 1-texture(textureAlpha, vertexUV_out).r;
	} else {
		finalColor.a = 1;
	}

    FragColor = finalColor;
}