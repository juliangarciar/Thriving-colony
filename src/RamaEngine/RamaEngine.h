#ifndef RAMAENGINE_H
#define RAMAENGINE_H

#include <GL/glew.h>
#include "RETypes.h"
#include "REAnimation.h"
#include "RECamera.h"
#include "RELight.h"
#include "REMesh.h"
#include "RESceneNode.h"
#include "ResourceManager/ResourceGLSL.h"
#include "Graphics/TNode.h"

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
        void Init();

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
         * @return RESceneNode* 
         */
        RESceneNode* createRESceneNode();

        /**
         * @brief 
         * 
         * @return RESceneNode* 
         */
        RESceneNode* createRESceneNode(RESceneNode* layer);
        
        /**
         * @brief 
         * 
         * @return REMesh* 
         */
        REMesh* createREMesh();
        
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
        REAnimation* createREAnimation();
        
        /**
         * @brief 
         * 
         * @return REAnimation* 
         */
        REAnimation* createREAnimation(RESceneNode* layer);

        /**
         * @brief 
         * 
         * @param rec 
         */
        void registerCamera(RECamera* rec);

        /**
         * @brief 
         * 
         * @param lightNode 
         */
        void registerLight(RELight* lightNode);

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

        RESceneNode *defaultSceneNode;

        // Punteros?
        std::vector<RECamera*> cameras;
        std::vector<RELight*> lights;

        // OpenGL
	GLuint vertexArrayID;
        GLuint programID;

        GLuint MVPID;
        GLuint projectionMatrixID;
        GLuint viewMatrixID;
        GLuint modelMatrixID;

        GLuint textureID;
};

#endif