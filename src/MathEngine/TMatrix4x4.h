#ifndef TMATRIX4X4_H
#define TMATRIX4X4_H

#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Types.h>

class TMatrix4x4 {
    public:
        TMatrix4x4();
        TMatrix4x4(glm::mat4);
        virtual ~TMatrix4x4();

        void identity();
        void invert();
        void transpose();

        TMatrix4x4 operator +(const TMatrix4x4 &p) const;
        TMatrix4x4 operator +(const f32 &num) const;
        TMatrix4x4 operator -(const TMatrix4x4 &p) const;
        TMatrix4x4 operator -(const f32 &num) const;
        TMatrix4x4 operator *(const TMatrix4x4 &p) const;
        TMatrix4x4 operator *(const f32 &num) const;
        TMatrix4x4 operator /(const TMatrix4x4 &p) const;
        TMatrix4x4 operator /(const f32 &num) const;

        glm::mat4 getMatrix() const;

    private:
        glm::mat4 m;
};

#endif