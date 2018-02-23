#ifndef RECAMERA_H
#define RECAMERA_H

#include <vector>
#include <algorithm>
#include <Types.h>
#include "TNode.h"
#include "TCamera.h"
#include "TTransform.h"
#include "TEnums.h"


class RECamera {
    public:
        /**
         * @brief 
         * 
         * @param parent 
         */
        RECamera(TNode* parent);

        /**
         * @brief 
         * 
         */
        ~RECamera();

        /**
         * @brief 
         * 
         * @param tX 
         * @param tY 
         * @param tZ 
         */
        void rotate(f32 rX, f32 rY, f32 rZ, f32 angle);

        /**
         * @brief 
         * 
         */
        void scale(f32 sX, f32 sY, f32 sZ);

        /**
         * @brief 
         * 
         */
        void translate(f32 tX, f32 tY, f32 tZ);

        

    private:

        TNode* cameraNode;
        TNode* rotationNode;
        TNode* translationNode;
        TNode* scaleNode;
        
};

#endif