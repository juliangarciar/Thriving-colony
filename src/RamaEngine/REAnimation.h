#ifndef REANIMATION_H
#define REANIMATION_H

#include "RETypes.h"
#include "RESceneNode.h"
#include "Graphics/TNode.h"
#include "Graphics/TTransform.h"
#include "Graphics/TAnimation.h"

class REAnimation {
    public:
        /**
         * @brief 
         * 
         * @param parent 
         */
        REAnimation(RESceneNode* parent);

        /**
         * @brief 
         * 
         */
        ~REAnimation();

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

        TNode* animationNode;
        TNode* rotationNode;
        TNode* translationNode;
        TNode* scaleNode;
        
};

#endif