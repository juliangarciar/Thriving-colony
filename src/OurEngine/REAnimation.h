#ifndef REANIMATION_H
#define REANIMATION_H

#include <vector>
#include <algorithm>
#include <Types.h>
#include "TNode.h"
#include "TAnimation.h"
#include "TTransform.h"



class REAnimation {
    public:
        /**
         * @brief 
         * 
         * @param parent 
         */
        REAnimation(TNode* parent);

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