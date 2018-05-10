#ifndef TTILE_H
#define TTILE_H

#include "TEntity.h"

class TTexture;
class ResourceIMG;

class TTile : public TEntity{
    public:
        TTile();
        TTile(ResourceIMG * _texture, glm::vec2 _position);
        virtual ~TTile();
        void beginDraw();
        void endDraw();
        void setTexture(ResourceIMG* _texture);
        void setPosition(glm::vec2 _position);
        glm::vec2 getPosition();
    private:
        TTexture* texture;
        GLuint textureID;
        //GLuint lightID;
        glm::vec2 position;
};
#endif