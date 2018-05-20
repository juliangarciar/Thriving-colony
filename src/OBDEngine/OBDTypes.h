#ifndef OBDTYPES_H
#define OBDTYPES_H

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <algorithm>

#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <cstdint>
#include <cstddef>
#include <thread>

typedef int32_t i32;
typedef uint32_t u32;
typedef float f32;

struct glslLight {
    glm::vec4 position;
    glm::vec4 intensity;

	GLfloat ambientCoeficient;
	GLfloat attenuationCoeficient;
	
    i32 type;
};

inline bool operator==(const glslLight& l, const glslLight& r) { return (l.position == r.position && l.intensity == r.intensity && l.ambientCoeficient == r.ambientCoeficient && l.attenuationCoeficient == r.attenuationCoeficient) == 0; }

struct glslMesh {
    std::vector<f32> vbo;
    std::vector<u32> ibo;
};

struct glslMaterial {
    glm::vec4 ambientColor;
    glm::vec4 diffuseColor;
    glm::vec4 specularColor;

	GLfloat shininess;
};

struct glslTexture {
    GLint diffuseTexture;
    GLint oclusionsTexture;
    GLint specularTexture;
    GLint alphaTexture;
};

struct OBDLine {
    glm::vec3 start;
    glm::vec3 end;
};

#endif