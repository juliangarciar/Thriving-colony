#ifndef TVERTEX_H
#define TVERTEX_H

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <Types.h>

class TVertex {
    public:
        TVertex(glm::vec3, glm::vec3, glm::vec2);
        ~TVertex();

        glm::vec3 getPosition();
        glm::vec3 getNormal();
        glm::vec2 getTextureCoordinate();
    private:
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 textureCoordinate;
};

#endif