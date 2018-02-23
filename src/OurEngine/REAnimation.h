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
         */
        void rotate();

        /**
         * @brief 
         * 
         */
        void scale();

        /**
         * @brief 
         * 
         */
        void translate();

    private:

        TNode* animationNode, rotationNode, translationNode, scaleNode;
        
};

#endif