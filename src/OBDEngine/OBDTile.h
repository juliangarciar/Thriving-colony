#ifndef OBDTILE_H
#define OBDTILE_H

#include "OBDEntity.h"

class OBDSceneNode;
class ResourceIMG;
class TNode;
class OBDTile : public OBDEntity{
    public:
        OBDTile();
        OBDTile(ResourceIMG* _texture, glm::vec2 _position);
        OBDTile(OBDSceneNode* parent, ResourceIMG* _texture, glm::vec2 _position);
        ~OBDTile();
        void setPosition(glm::vec2 _position);
        void setTexture(ResourceIMG* _texture);
        void setID(GLuint _id);
        GLuint getID();
        TNode* getFirstNode();
    private:
        TNode* tileNode;
        glm::vec2 position;
        GLuint ID;
};

#endif