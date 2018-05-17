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
        OBDAnimation(OBDSceneNode* parent);

        /**
         * @brief 
         * 
         */
        ~OBDAnimation();

    private:
        TNode* animationNode;
};

#endif