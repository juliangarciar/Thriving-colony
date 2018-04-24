#include "TTile.h"
#include "TTexture.h"
#include "../ResourceManager/ResourceIMG.h"

#define MAX_LIGHTS 10

TTile::TTile(){
    texture = nullptr;
}
TTile::TTile(ResourceIMG* _texture, glm::vec2 _position){
    texture = new TTexture(_texture);
    textureID = texture->getTextureID();
    position = _position;
}
TTile::~TTile(){
    //ToDo: Revisalo julian
    delete texture;
}
void TTile::beginDraw(){
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    //glPushMatrix();
        //glTranslatef(position[1], position[0], 5.0);

        glBegin(GL_QUADS);
            glTexCoord2d(0.0, 0.0);
            glVertex3f(float(position[0]), float(position[1]), 0.0);

            glTexCoord2d(1.0, 0.0);
            glVertex3f(float(position[0] + 1), float(position[1]), 0.0);

            glTexCoord2d(1.0, 1.0);
            glVertex3f(float(position[0] + 1), float(position[1] + 1), 0.0);

            glTexCoord2d(0.0, 1.0);
            glVertex3f(0.0, float(position[1] + 1), 0.0);
        glEnd();
    //glPopMatrix();
}
void TTile::endDraw(){

}
void TTile::setTexture(ResourceIMG* _texture){
    if(texture == nullptr)
        texture = new TTexture(_texture);
    else{
        delete texture;
        texture = new TTexture(_texture);
    }
    textureID = texture->getTextureID();
}
void TTile::setPosition(glm::vec2 _position){
    position = _position;
}
glm::vec2 TTile::getPosition(){
    return position;
}