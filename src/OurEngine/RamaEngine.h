#ifndef RAMAENGINE_H
#define RAMAENGINE_H

#include <GL/glew.h>
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
         */
        void initializeOpenGL();

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
         * @return RELight* 
         */
        RELight* createRELight(RESceneNode* layer);

        /**
         * @brief 
         * 
         * @return RECamera* 
         */
        RECamera* createRECamera(RESceneNode* layer);
        
        /**
         * @brief 
         * 
         * @return REMesh* 
         */
        REMesh* createREMesh(RESceneNode* layer);
        
        /**
         * @brief 
         * 
         * @return REAnimation* 
         */
        REAnimation* createREAnimation(RESceneNode* layer);

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

        /**
         * @brief 
         * 
         * @param cameraNode 
         */
        void registerCamera(TNode* cameraNode);

        /**
         * @brief 
         * 
         * @param lightNode 
         */
        void registerLight(TNode* lightNode);

        /**
         * @brief 
         * 
         * @param sceneNode 
         */
        void registerSceneNode(TNode* sceneNode);


    private:
        static RamaEngine* instance;

        TNode* rootNode;

        RESceneNode *defaultSceneNode;

        // Punteros?
        std::vector<TNode*> cameras;
        std::vector<TNode*> lights;
        std::vector<TNode*> sceneNodes;
};

#endif