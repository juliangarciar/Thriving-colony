#include "TTile.h"
#include "TTexture.h"

TTile::TTile(){
    texture = nullptr;
}
TTile::TTile(TTexture* _texture, glm::vec2 _position){
    texture = _texture;
    position = _position;
}
TTile::~TTile(){

}
void TTile::beginDraw(){
    //glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    //glUniform1i
    glPushMatrix();
        glTranslatef(position[0], position[1], 0);

        glBegin(GL_QUADS);
            glTexCoord2d(0.0, 0.0);
            glVertex3f(0.0, 0.0, 0.0);

            glTexCoord2d(1.0, 0.0);
            glVertex3f(1.0, 0.0, 0.0);

            glTexCoord2d(1.0, 1.0);
            glVertex3f(1.0, 1.0, 0.0);

            glTexCoord2d(0.0, 1.0);
            glVertex3f(0.0, 1.0, 0.0);
        glEnd();
    glPopMatrix();
}
void TTile::endDraw(){

}
void TTile::setTexture(TTexture* _texture){
    texture = _texture;
    glBindBuffer(GL_UNIFORM_BUFFER, textureID);
    //glBufferBufferRange(GL_UNIFORM_BUFFER, cache.getID(OBDEnums::OpenGLIDs::BUFFER_TEXTURE), textureID, 0, glslTexture);
}
void TTile::setPosition(glm::vec2 _position){
    position = _position;
}
glm::vec2 TTile::getPosition(){
    return position;
}