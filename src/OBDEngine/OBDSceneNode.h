#ifndef OBDSCENENODE_H
#define OBDSCENENODE_H

#include "OBDTypes.h"
#include "Graphics/TNode.h"
#include "Graphics/TTransform.h"

class OBDSceneNode {
    public:
        /**
         * @brief 
         * 
         * @param parent 
         */
        OBDSceneNode(TNode*);

        /**
         * @brief 
         * 
         * @param parent 
         */
        OBDSceneNode(OBDSceneNode*);

        /**
         * @brief 
         * 
         */
        ~OBDSceneNode();

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