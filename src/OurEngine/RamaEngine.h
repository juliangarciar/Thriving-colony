#ifndef RAMAENGINE_H
#define RAMAENGINE_H

#include <vector>
#include <algorithm>
#include <Types.h>
#include "TNode.h"
#include "REAnimation.h"
#include "RECamera.h"
#include "RELight.h"
#include "REMesh.h"
#include "RESceneNode.h"

class RamaEngine {
    public:
        /**
         * @brief 
         * 
         */
        RamaEngine();

        /**
         * @brief 
         * 
         */
        ~RamaEngine();

        /**
         * @brief 
         * 
         * @return RELight* 
         */
        RELight* createRELight();

        /**
         * @brief 
         * 
         * @return RECamera* 
         */
        RECamera* createRECamera();
        
        /**
         * @brief 
         * 
         * @return REMesh* 
         */
        REMesh* createREMesh();
        
        /**
         * @brief 
         * 
         * @return REAnimation* 
         */
        REAnimation* createREAnimation();

        /**
         * @brief 
         * 
         * @return RESceneNode* 
         */
        RESceneNode* createRESceneNode();

        /**
         * @brief 
         * 
         */
        void draw();

        /**
         * @brief 
         * 
         * @return TNode* 
         */
        TNode* getRootNode();

        /**
         * @brief 
         * 
         */
        RESceneNode* getDefaultLayer();

    private:
        TNode* rootNode;
        RESceneNode* defaultLayer;
};

#endif