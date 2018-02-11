#include "TTransform.h"

TTransform::TTransform() : TEntity() {

}

TTransform::~TTransform() {

}

void TTransform::beginDraw(){

}

void TTransform::endDraw(){

}

void TTransform::identity() {

}

void TTransform::load(TMatrix4x4 newMatrix) {
    matrix = newMatrix;
}

void TTransform::transpose() {

}

void TTransform::invert() {

}

void TTransform::multiply(f32 factor) {

}

void TTransform::translate(f32 x, f32 y, f32 z) {

}

void TTransform::rotate(f32 x, f32 y, f32 z, f32 h) {

}

void TTransform::scale(f32 factor) {

}

void beginDraw() {

}

void endDraw() {

}