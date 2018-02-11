#ifndef TTRANSFORM_H
#define TTRANSFORM_H

#include "TEntity.h"
#include <Types.h>
#include <MathEngine/TMatrix4x4.h>

class TTransform : public TEntity {
    public:
        TTransform();
        virtual ~TTransform();

        void beginDraw();
        void endDraw();

        // Matrix operations
        void identity();
        void load(TMatrix4x4);
        void transpose();
        void invert();
        void multiply(f32);
        // TBA

        // Basic transforms
        void translate(f32, f32, f32);
        void rotate(f32, f32, f32, f32);
        void scale(f32);
        // TBA

    private:

        TMatrix4x4 matrix;
};

#endif