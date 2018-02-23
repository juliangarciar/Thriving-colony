#ifndef REMESH_H
#define REMESH_H

#include <vector>
#include <algorithm>
#include <Types.h>
#include "TNode.h"
#include "TMesh.h"
#include "TTransform.h"



class REMesh {
    public:
        /**
         * @brief 
         * 
         * @param parent 
         */
        REMesh(TNode* parent);

        /**
         * @brief 
         * 
         */
        ~REMesh();

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

        TNode* meshNode, rotationNode, translationNode, scaleNode;
        
};

#endif