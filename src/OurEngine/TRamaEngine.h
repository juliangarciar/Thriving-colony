#ifndef TRAMAENGINE_H
#define TRAMAENGINE_H

#include <vector>
#include <algorithm>
#include <Types.h>
#include "TNode.h"
#include "TTransform.h"
#include "TCamera.h"
#include "TLight.h"
#include "TMesh.h"

class TRamaEngine {
    public:
        /**
         * @brief 
         * 
         */
        TRamaEngine();

        /**
         * @brief 
         * 
         */
        ~TRamaEngine();

        ///////////
        ///NODOS
        ///////////

        /**
         * @brief 
         * 
         * @return TNode* 
         */
        void init();

        ///////////
        ///ENTIDADES
        ///////////

        /**
         * @brief 
         * 
         * @return TTransform* 
         */
        TTransform* createTransform();

        /**
         * @brief 
         * 
         * @return TCamera* 
         */
        TCamera* createCamera();

        /**
         * @brief 
         * 
         * @return TLight* 
         */
        TLight* createLight();

        /**
         * @brief 
         * 
         * @return TMesh* 
         */
        TMesh* createMesh();

    private:
        TNode* sceneNode;
};

#endif