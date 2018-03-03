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

        /**
         * @brief 
         * 
         * @return TNode* 
         */
        TNode* getSceneNode();

    private:
        TNode* sceneNode;
        TNode* rotationNode;
        TNode* translationNode;
        TNode* scaleNode;
};

#endif