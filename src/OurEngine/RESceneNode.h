#ifndef RESCENENODE_H
#define RESCENENODE_H

#include <vector>
#include <algorithm>
#include <Types.h>
#include "TNode.h"
#include "REMesh.h"
#include "TTransform.h"



class RESceneNode {
    public:
        /**
         * @brief 
         * 
         * @param parent 
         */
        RESceneNode(TNode* parent);

        /**
         * @brief 
         * 
         */
        ~RESceneNode();

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
        TNode* sceneNode, rotationNode, translationNode, scaleNode;
};

#endif