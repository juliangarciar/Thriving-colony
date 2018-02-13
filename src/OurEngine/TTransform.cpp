#include "TTransform.h"

TTransform::TTransform() : TEntity() {
    matrix = glm::mat4();
}

TTransform::~TTransform() {
    delete matrix;
}

void TTransform::beginDraw(){
    matrixStack.push(matrix);
}

void TTransform::endDraw(){
    matrixStack.pop();
}

void TTransform::identity() {
    matrix = glm::mat4();
}

void TTransform::load(glm::mat4 newMatrix) {
    matrix = newMatrix;
}

void TTrasform::transpose(); {
    matrix = glm::transpose(matrix);
}

void TTransform::invert() {
    matrix = glm::inverse(matrix);
}

void TTransform::multiply(f32 mFactor) {
    matrix = matrix * mFactor;
}

void TTransform::multiply(glm::vec3 mVector) {
    matrix = matrix * mVector;
}

void TTransform::multiply(glm::mat4 matrix) {
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

void beginDraw() {

}

void endDraw() {

}