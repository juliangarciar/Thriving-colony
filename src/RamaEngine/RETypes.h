#ifndef RETYPES_H
#define RETYPES_H

#include <GL/glew.h>
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

struct Light {
    i32 shininess;
    glm::vec3 color;
};

struct Material {
    glm::vec3 ambientColor;
    glm::vec3 diffuseColor;
    glm::vec3 specularColor;
};

struct Texture {
    GLuint type;
    GLuint textureID;
};

#endif