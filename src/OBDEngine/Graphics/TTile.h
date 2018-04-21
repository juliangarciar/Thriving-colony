#ifndef TTILE_H
#define TTILE_H

#include "TEntity.h"
#include <GL/glew.h>

class TTexture;

class TTile : public TEntity{
    public:
        TTile();
        TTile(TTexture* _texture, glm::vec2 _position);
        ~TTile();
        void beginDraw();
        void endDraw();
        void setTexture(TTexture* _texture);
        void setPosition(glm::vec2 _position);
        glm::vec2 getPosition();
    private:
        TTexture* texture;
        GLuint textureID;
        glm::vec2 position;
};
#endif