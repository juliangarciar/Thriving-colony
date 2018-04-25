#ifndef OBDANIMATION_H
#define OBDANIMATION_H

#include "OBDEntity.h"
#include "OBDSceneNode.h"

#include "Graphics/TTransform.h"
#include "Graphics/TAnimation.h"

class OBDAnimation : public OBDEntity {
    public:
        /**
         * @brief 
         * 
         * @param parent 
         */
        OBDAnimation();

        /**
         * @brief 
         * 
         * @param parent 
         */
        OBDAnimation(OBDSceneNode* parent);

        /**
         * @brief 
         * 
         */
        virtual ~OBDAnimation();

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
         * @brief Get the First Node object
         * 
         * @return TNode* 
         */
        TNode *getFirstNode();
    private:
        TNode* rotationNode;
        TNode* translationNode;
        TNode* scaleNode;

        TNode* animationNode;
};

#endif