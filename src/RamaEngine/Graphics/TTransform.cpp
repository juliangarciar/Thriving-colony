#include "TTransform.h"

TTransform::TTransform() : TEntity() {
    matrix = glm::mat4(1.0f);
}

TTransform::~TTransform() {
    
}

void TTransform::beginDraw(){
    matrixStack.push(matrix);
    // Por la derecha
	glm::mat4 mM = *TMatrixCache::Instance()->getMatrix(REEnums::Matrices::MATRIX_MODEL);
    mM = mM * matrix;
    TMatrixCache::Instance()->setMatrix(REEnums::Matrices::MATRIX_MODEL, &mM);
}

void TTransform::endDraw() {
    matrixStack.pop();
    // Por la inversa por la izquierda
	glm::mat4 mM = *TMatrixCache::Instance()->getMatrix(REEnums::Matrices::MATRIX_MODEL);
    mM = glm::inverse(matrix) * mM;
    TMatrixCache::Instance()->setMatrix(REEnums::Matrices::MATRIX_MODEL, &mM);
}

void TTransform::identity() {
    matrix = glm::mat4(1.0f);
}

void TTransform::load(glm::mat4 newMatrix) {
    matrix = newMatrix;
}

void TTransform::transpose() {
    matrix = glm::transpose(matrix);
}

void TTransform::invert() {
    matrix = glm::inverse(matrix);
}

void TTransform::multiply(f32 mFactor) {
    matrix = matrix * mFactor;
}

void TTransform::multiply(glm::vec3 mVector) {
    glm::vec4 result = glm::vec4(mVector, 1.0 );
    result = matrix * result;
}

void TTransform::multiply(glm::mat4 mMatrix) {
    matrix = matrix * mMatrix;
}

void TTransform::translate(f32 tX, f32 tY, f32 tZ) {
    matrix = glm::translate(matrix, glm::vec3(tX, tY, tZ));
}

void TTransform::rotate(f32 rX, f32 rY, f32 rZ, f32 angle) {
    matrix = glm::rotate(matrix , angle,glm::vec3(rX, rY, rZ));

}

void TTransform::scale(f32 sX, f32 sY, f32 sZ) {
    matrix = glm::scale(matrix, glm::vec3(sX, sY, sZ));
}

glm::mat4 TTransform::getMatrix() {
    return matrix;
}