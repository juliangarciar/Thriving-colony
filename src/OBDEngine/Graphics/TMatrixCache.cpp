#include "TMatrixCache.h"

TMatrixCache* TMatrixCache::pinstance = 0;

TMatrixCache* TMatrixCache::Instance() {
    if (pinstance == 0) {
        pinstance = new TMatrixCache();
    }
    return pinstance;
}

TMatrixCache::TMatrixCache() {
    currentMatrix = glm::mat4(1.0f);
    identityMatrix = glm::mat4(1.0f);
    for (int i = 0; i < OBDEEnums::Matrices::MATRICES; i++){
        matrices.push_back(&identityMatrix);
    }
    for (int i = 0; i < OBDEEnums::Matrices::MATRICES; i++){
        matrixIDs.push_back(0);
    }
}

TMatrixCache::~TMatrixCache() {
    
}

void TMatrixCache::setMatrix(OBDEEnums::Matrices t, glm::mat4 *m){
    matrices[t] = m;
}

glm::mat4 *TMatrixCache::getMatrix(OBDEEnums::Matrices t){
    return matrices.at(t);
}

void TMatrixCache::setMatrixID(OBDEEnums::Matrices t, GLuint i){
    matrixIDs[t] = i;
}

GLuint TMatrixCache::getMatrixID(OBDEEnums::Matrices t){
    return matrixIDs.at(t);
}

void TMatrixCache::setCurrentMatrix(const glm::mat4& m) {
    currentMatrix = m;
}

glm::mat4& TMatrixCache::getCurrentMatrix() {
    return currentMatrix;
}

std::deque<glm::mat4>& TMatrixCache::getMatrixStack() {
    return matrixStack;
}