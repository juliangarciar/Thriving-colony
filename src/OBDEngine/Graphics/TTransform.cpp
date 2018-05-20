#include "TTransform.h"

TTransform::TTransform() : TEntity() {
    matrix = glm::mat4(1.0f);
}

TTransform::~TTransform() {
    
}

void TTransform::beginDraw() {
    cache.getMatrixStack().push(matrix * cache.getMatrixStack().top());
}

void TTransform::endDraw() {
    cache.getMatrixStack().pop();
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

void TTransform::translate(glm::vec3 t) {
    matrix = glm::translate(matrix, t);
}

void TTransform::rotate(glm::vec3 r, f32 angle) {
    matrix = glm::rotate(matrix, glm::radians(angle), r);
}

void TTransform::scale(glm::vec3 s) {
    matrix = glm::scale(matrix, s);
}

glm::mat4 TTransform::getMatrix() {
    return matrix;
}