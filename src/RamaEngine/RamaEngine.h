#ifndef RAMAENGINE_H
#define RAMAENGINE_H

#include <GL/glew.h>

#include "RETypes.h"
#include "REEnums.h"
#include "REAnimation.h"
#include "REBillboard.h"
#include "RECamera.h"
#include "RELight.h"
#include "REMesh.h"
#include "RESceneNode.h"
#include "REShaderProgram.h"

#include "ResourceManager/ResourceManager.h"
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
         */
        void End();

        /**
         * @brief 
         * 
         * @return RELight* 
         */
        RELight* createLight(REColor color, u32 intensity);

        /**
         * @brief 
         * 
         * @return RECamera* 
         */
        RECamera* createCamera();

        /**
         * @brief 
         * 
         * @return RESceneNode* 
         */
        RESceneNode* createSceneNode();

        /**
         * @brief 
         * 
         * @param 
         * @return RESceneNode* 
         */
        RESceneNode* createSceneNode(RESceneNode*);
        
        /**
         * @brief 
         * 
         * @param 
         * @return REMesh* 
         */
        REMesh* createMesh(std::string);
        
        /**
         * @brief 
         * 
         * @param 
         * @param 
         * @return REMesh* 
         */
        REMesh* createMesh(RESceneNode*, std::string);
        
        /**
         * @brief 
         * 
         * @param 
         * @return REAnimation* 
         */
        REAnimation* createAnimation(std::string);
        
        /**
         * @brief 
         * 
         * @param 
         * @param 
         * @return REAnimation* 
         */
        REAnimation* createAnimation(RESceneNode*, std::string);

        /**
         * @brief Create a Shader Program object
         * 
         * @param a 
         * @param b 
         * @param c 
         * @return REShaderProgram* 
         */
        REShaderProgram *createShaderProgram(std::string, std::string, std::string);

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
         * @param shaderProgram 
         * @param shaderProgram 
         */
        void registerShaderProgram(std::string, REShaderProgram *);

        /**
         * @brief Set the current shader program
         * @param program
         */
        void setCurrentShaderProgram(std::string);

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
        TMatrixCache *matrixCache;

        ResourceManager *REManager;

        TNode* rootNode;

        RESceneNode *clSceneNode;
        RESceneNode *defaultSceneNode;

        REShaderProgram *currentProgram;

        std::vector<RECamera*> cameras;
        std::vector<RELight*> lights;
        std::map<std::string, REShaderProgram*> shaderPrograms;

        // OpenGL
	    GLuint vertexArrayID;
        GLuint programID;
};

#endif