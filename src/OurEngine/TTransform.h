#ifndef TTRANSFORM_H
#define TTRANSFORM_H

#include "TEntity.h"
#include <Types.h>
#include <stack>  
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

class TTransform : public TEntity {
    public:
        /**
         * @brief 
         * 
         */
        TTransform();
        /**
         * @brief 
         * 
         */
        virtual ~TTransform();
        /**
         * @brief 
         * 
         */
        void beginDraw();
        /**
         * @brief 
         * 
         */
        void endDraw();

        // Matrix operations
        /**
         * @brief 
         * 
         */
        void identity();
        /**
         * @brief 
         * 
         * @param glm::mat4 
         */
        void load(glm::mat4);
        /**
         * @brief 
         * 
         */
        void transpose();
        /**
         * @brief 
         * 
         */
        void invert();
        /**
         * @brief 
         * 
         * @param f32 
         */
        void multiply(f32);
        /**
         * @brief 
         * 
         * @param glm::vec3 
         */
        void multiply(glm::vec3);
        /**
         * @brief 
         * 
         * @param glm::mat4 
         */
        void multiply(glm::mat4);
        // TBA

        // Basic transforms
        /**
         * @brief 
         * 
         * @param f32 
         * @param f32 
         * @param f32 
         */
        void translate(f32, f32, f32);
        /**
         * @brief 
         * 
         * @param f32 
         * @param f32 
         * @param f32 
         * @param f32 
         */
        void rotate(f32, f32, f32, f32);
        /**
         * @brief 
         * 
         * @param f32 
         * @param f32 
         * @param f32 
         */
        void scale(f32, f32, f32);
        
    private:

        glm::mat4 matrix;
};

#endif