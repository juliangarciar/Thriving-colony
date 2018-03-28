#include "TCache.h"

TCache::TCache() {
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    for (int i = 0; i < (int)REEnums::OpenGLIDs::PARAMS; i++){
        parameterIDs.push_back(0);
    }
    lights = new std::vector<glslLight>();
}

TCache::~TCache() {
    
}

std::vector<GLuint> TCache::generateAllIDs(GLuint programID){
    GLuint paramIDs[REEnums::OpenGLIDs::PARAMS];

	// Get a handle for our "MVP" uniform
    paramIDs[REEnums::OpenGLIDs::MATRIX_PROJECTION] = glGetUniformLocation(programID, "P");
	paramIDs[REEnums::OpenGLIDs::MATRIX_VIEW] = glGetUniformLocation(programID, "V");
	paramIDs[REEnums::OpenGLIDs::MATRIX_MODEL] = glGetUniformLocation(programID, "M");
	paramIDs[REEnums::OpenGLIDs::MATRIX_MV] = glGetUniformLocation(programID, "MV");
	paramIDs[REEnums::OpenGLIDs::MATRIX_MVP] = glGetUniformLocation(programID, "MVP");

	paramIDs[REEnums::OpenGLIDs::BUFFER_LIGHT] = glGetUniformBlockIndex(programID, "LightBuffer");
	paramIDs[REEnums::OpenGLIDs::BUFFER_MATERIAL] = glGetUniformBlockIndex(programID, "MaterialBuffer");
	paramIDs[REEnums::OpenGLIDs::BUFFER_TEXTURE] = glGetUniformBlockIndex(programID, "TextureBuffer");

	glUniformBlockBinding(programID, paramIDs[REEnums::OpenGLIDs::BUFFER_LIGHT], 1);
	glUniformBlockBinding(programID, paramIDs[REEnums::OpenGLIDs::BUFFER_MATERIAL], 2);
	glUniformBlockBinding(programID, paramIDs[REEnums::OpenGLIDs::BUFFER_TEXTURE], 3);

    paramIDs[REEnums::OpenGLIDs::SAMPLER_AMBIENT] = glGetUniformLocation(programID, "textureAmbient");
	paramIDs[REEnums::OpenGLIDs::SAMPLER_DIFFUSE] = glGetUniformLocation(programID, "textureDiffuse");
	paramIDs[REEnums::OpenGLIDs::SAMPLER_SPECULAR] = glGetUniformLocation(programID, "textureSpecular");
	paramIDs[REEnums::OpenGLIDs::SAMPLER_ALPHA] = glGetUniformLocation(programID, "textureAlpha");
	paramIDs[REEnums::OpenGLIDs::SAMPLER_BUMP] = glGetUniformLocation(programID, "textureBump");


    return std::vector<GLuint>(paramIDs, paramIDs + REEnums::OpenGLIDs::PARAMS);
}

void TCache::setAllIDs(std::vector<GLuint> v){
    parameterIDs = v;
}

void TCache::setID(REEnums::OpenGLIDs s, GLuint i){
    parameterIDs[(int)s] = i;
}

GLuint TCache::getID(REEnums::OpenGLIDs s){
    return parameterIDs[(int)s];
}

void TCache::setModelMatrix(glm::mat4 m){
    modelMatrix = m;
}

glm::mat4 TCache::getModelMatrix(){
    return modelMatrix;
}

void TCache::setViewMatrix(glm::mat4 m){
    viewMatrix = m;
}

glm::mat4 TCache::getViewMatrix(){
    return viewMatrix;
}

void TCache::setProjectionMatrix(glm::mat4 m){
    projectionMatrix = m;
}

glm::mat4 TCache::getProjectionMatrix(){
    return projectionMatrix;
}

std::vector<glslLight> *TCache::getLights(){
    return lights;
}

std::stack<glm::mat4>& TCache::getMatrixStack() {
    return matrixStack;
}