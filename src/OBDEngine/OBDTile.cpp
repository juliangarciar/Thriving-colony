#include "OBDTile.h"
#include "OBDSceneNode.h"
#include "ResourceManager/ResourceIMG.h"
#include "Graphics/TTile.h"

OBDTile::OBDTile():
                tileNode(nullptr),
                position(glm::vec2())
{}
OBDTile::OBDTile(ResourceIMG* _texture, glm::vec2 _position){
    tileNode = new TNode(new TTile(_texture, _position));
    position = _position;
}
OBDTile::OBDTile(OBDSceneNode* _parent, ResourceIMG* _texture, glm::vec2 _position){
    tileNode = new TNode(new TTile(_texture, _position));
    position = _position;
    _parent->addChild(this);
}
OBDTile::~OBDTile(){
    delete tileNode;
}
void OBDTile::setPosition(glm::vec2 _position){
    position = _position;
    TTile* tmp = (TTile*)tileNode->getEntity();
    tmp->setPosition(_position);
}
void OBDTile::setTexture(ResourceIMG* _texture){
    TTile* tmp = (TTile*)tileNode->getEntity();
    tmp->setTexture(_texture);
}
void OBDTile::setID(GLuint _id){
	ID = _id;
}
GLuint OBDTile::getID(){
	return ID;
}
TNode* OBDTile::getFirstNode(){
    return tileNode;
}