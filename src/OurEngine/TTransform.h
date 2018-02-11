#ifndef TTRANSFORM_H
#define TTRANSFORM_H

#include "TEntity.h"
#include "../Types.h"

class TTransform : public TEntity {
    public:
    TTransform();
    ~TTransform();

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

    virtual void beginDraw();
    virtual void endDraw();

    private:

    TMatrix4x4 matrix;
};

#endif