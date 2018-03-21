#ifndef OBDEANIMATION_H
#define OBDEANIMATION_H

#include "OBDETypes.h"
#include "OBDESceneNode.h"
#include "Graphics/TNode.h"
#include "Graphics/TTransform.h"
#include "Graphics/TAnimation.h"

class OBDEAnimation {
    public:
        /**
         * @brief 
         * 
         * @param parent 
         */
        OBDEAnimation(OBDESceneNode* parent);

        /**
         * @brief 
         * 
         */
        ~OBDEAnimation();

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