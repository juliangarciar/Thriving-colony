#ifndef OBDESCENENODE_H
#define OBDESCENENODE_H

#include "OBDETypes.h"
#include "Graphics/TNode.h"
#include "Graphics/TTransform.h"

class OBDESceneNode {
    public:
        /**
         * @brief 
         * 
         * @param parent 
         */
        OBDESceneNode(TNode*);

        /**
         * @brief 
         * 
         * @param parent 
         */
        OBDESceneNode(OBDESceneNode*);

        /**
         * @brief 
         * 
         */
        ~OBDESceneNode();

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