#ifndef TTRANSFORM_H
#define TTRANSFORM_H

#include "TEntity.h"
#include <Types.h>
#include <stack>  
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transformation.hpp>

class TTransform : public TEntity {
    public:
        TTransform();
        virtual ~TTransform();

        void beginDraw();
        void endDraw();

        // Matrix operations
        
        void identity();
        void load(glm::mat4);
        void transpose();
        void invert();
        void multiply(f32);
        void multiply(glm::vec3);
        void multiply(glm::mat4);
        // TBA

        // Basic transforms
        void translate(f32, f32, f32);
        void rotate(f32, f32, f32, f32);
        void scale(f32, f32, f32);
        // TBA

    private:

        glm::mat4 matrix;
};

#endif