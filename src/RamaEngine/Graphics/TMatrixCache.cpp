#include "TMatrixCache.h"

TMatrixCache* TMatrixCache::pinstance = 0;

TMatrixCache* TMatrixCache::Instance() {
    if (pinstance == 0) {
        pinstance = new TMatrixCache();
    }
    return pinstance;
}

TMatrixCache::TMatrixCache() {
    identityMatrix = glm::mat4(1.0f);
    for (int i = 0; i < REEnums::Matrices::MATRICES; i++){
        matrices.push_back(&identityMatrix);
    }
    for (int i = 0; i < REEnums::Matrices::MATRICES; i++){
        matrixIDs.push_back(0);
    }
}

TMatrixCache::~TMatrixCache() {
    
}

void TMatrixCache::setMatrix(REEnums::Matrices t, glm::mat4 *m){
    matrices[t] = m;
}

glm::mat4 *TMatrixCache::getMatrix(REEnums::Matrices t){
    return matrices.at(t);
}

void TMatrixCache::setMatrixID(REEnums::Matrices t, GLuint i){
    matrixIDs[t] = i;
}

GLuint TMatrixCache::getMatrixID(REEnums::Matrices t){
    return matrixIDs.at(t);
}