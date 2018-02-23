#ifndef RELIGHT_H
#define RELIGHT_H

#include <vector>
#include <algorithm>
#include <Types.h>
#include "TNode.h"
#include "TLight.h"
#include "TTransform.h"



class RELight {
    public:
        /**
         * @brief 
         * 
         * @param parent 
         */
        RELight(TNode* parent);

        /**
         * @brief 
         * 
         */
        ~RELight();

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

        TNode* lightNode, rotationNode, translationNode, scaleNode;
        
};

#endif