#ifndef OBDTYPES_H
#define OBDTYPES_H

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

struct glslMaterial {
    glm::vec3 ambientColor;
    glm::vec3 diffuseColor;
    glm::vec3 specularColor;
};

struct glslTexture {
    bool ambientTexture;
    bool diffuseTexture;
    bool specularTexture;
    bool alphaTexture;
    bool bumpTexture;
};

#endif