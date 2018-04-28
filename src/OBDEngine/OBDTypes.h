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
#include <thread>

typedef int32_t i32;
typedef uint32_t u32;
typedef unsigned short us32;
typedef float f32;

struct glslLight {
    glm::vec3 position;

    glm::vec3 ambientComponent;
    glm::vec3 diffuseComponent;
    glm::vec3 specularComponent;
};

inline bool operator==(const glslLight& l, const glslLight& r){ return (l.position == r.position && l.ambientComponent == r.ambientComponent && l.diffuseComponent == r.diffuseComponent && l.specularComponent == r.specularComponent) == 0; }

struct glslMaterial {
    glm::vec3 ambientColor;
    glm::vec3 diffuseColor;
    glm::vec3 specularColor;
};

struct glslTexture {
    GLint ambientTexture;
    GLint diffuseTexture;
    GLint specularTexture;
    GLint alphaTexture;
    GLint bumpTexture;
};

struct OBDLine {
    glm::vec3 start;
    glm::vec3 end;
};

#endif