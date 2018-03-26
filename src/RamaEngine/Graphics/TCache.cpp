#include "TCache.h"

TCache::TCache() {
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    for (int i = 0; i < (int)REEnums::ShaderParams::PARAMS; i++){
        parameterIDs.push_back(0);
    }
    lights = new std::vector<Light>();
}

TCache::~TCache() {
    
}

void TCache::setCurrentProgramID(GLuint u){
    currentProgramID = u;
}

GLuint TCache::getCurrentProgramID(){
    return currentProgramID;
}

std::vector<GLuint> TCache::generateAllParamIDs(int programID){
    GLuint paramIDs[REEnums::ShaderParams::PARAMS];

	// Get a handle for our "MVP" uniform
    paramIDs[REEnums::ShaderParams::MATRIX_PROJECTION] = glGetUniformLocation(programID, "P");
	paramIDs[REEnums::ShaderParams::MATRIX_VIEW] = glGetUniformLocation(programID, "V");
	paramIDs[REEnums::ShaderParams::MATRIX_MODEL] = glGetUniformLocation(programID, "M");
	paramIDs[REEnums::ShaderParams::MATRIX_MV] = glGetUniformLocation(programID, "MV");
	paramIDs[REEnums::ShaderParams::MATRIX_MVP] = glGetUniformLocation(programID, "MVP");

	paramIDs[REEnums::ShaderParams::BUFFER_LIGHT] = glGetUniformBlockIndex(programID, "Light");
	paramIDs[REEnums::ShaderParams::BUFFER_MATERIAL] = glGetUniformBlockIndex(programID, "Material");
	paramIDs[REEnums::ShaderParams::BUFFER_TEXTURE] = glGetUniformBlockIndex(programID, "Texture");

    return std::vector<GLuint>(paramIDs, paramIDs + REEnums::ShaderParams::PARAMS);
}

void TCache::setAllParamIDs(std::vector<GLuint> v){
    parameterIDs = v;
}

void TCache::setParamID(REEnums::ShaderParams s, GLuint i){
    parameterIDs[(int)s] = i;
}

GLuint TCache::getParamID(REEnums::ShaderParams s){
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

std::vector<Light> *TCache::getLights(){
    return lights;
}

std::stack<glm::mat4>& TCache::getMatrixStack() {
    return matrixStack;
}