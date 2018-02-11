#include "TMatrix4x4"

TMatrix4x4::TMatrix4x4() {
    m = glm::mat4();
}

TMatrix4x4::~TMatrix4x4() {
    delete m;
}

void TMatrix4x4::identity() {
    m = glm::mat4();
}

void TMatrix4x4::invert() {
    m = glm::inverse(m);
}

void TMatrix4x4::transpose() {
    m = glm::transpose(m);
}

glm::mat4<f32> * getMatrix() {
    return m;
}

TMatrix4x4 TMatrix4x4::operator + (const TMatrix4x4 &p) const {
    return TMatrix4x4(this -> m + p);
}

TMatrix4x4 TMatrix4x4::operator + (const f32 &p) const {
    return TMatrix4x4(this -> m + p);
}

TMatrix4x4 TMatrix4x4::operator - (const TMatrix4x4 &p) const {
    return TMatrix4x4(this -> m - p);
}

TMatrix4x4 TMatrix4x4::operator - (const f32 &p) const {
    return TMatrix4x4(this -> x - p);
}

TMatrix4x4 TMatrix4x4::operator * (const TMatrix4x4 &p) const {
    return TMatrix4x4(this -> m * p);
}

TMatrix4x4 TMatrix4x4::operator * (const f32 &p) const {
    return TMatrix4x4(this -> m * p);
}

TMatrix4x4 TMatrix4x4::operator / (const TMatrix4x4 &p) const {
    return TMatrix4x4(this -> m / p);
}

TMatrix4x4 TMatrix4x4::operator / (const f32 &p) const {
    return TMatrix4x4(this -> m / p);
}