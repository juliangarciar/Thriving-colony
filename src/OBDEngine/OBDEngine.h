#ifndef OBDENGINE_H
#define OBDENGINE_H

#include <GL/glew.h>

#include "OBDETypes.h"
#include "OBDEEnums.h"
#include "OBDEAnimation.h"
#include "OBDEBillboard.h"
#include "OBDECamera.h"
#include "OBDELight.h"
#include "OBDEMesh.h"
#include "OBDESceneNode.h"
#include "OBDEShaderProgram.h"

#include "ResourceManager/ResourceManager.h"
#include "Graphics/TNode.h"

class OBDEngine {
    public:
        /**
         * @brief 
         * 
         */
        OBDEngine();

        /**
         * @brief 
         * 
         */
        ~OBDEngine();

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
         * @return OBDELight* 
         */
        OBDELight* createLight(OBDEColor color, u32 intensity);

        /**
         * @brief 
         * 
         * @return OBDECamera* 
         */
        OBDECamera* createCamera();

        /**
         * @brief 
         * 
         * @return OBDESceneNode* 
         */
        OBDESceneNode* createSceneNode();

        /**
         * @brief 
         * 
         * @param 
         * @return OBDESceneNode* 
         */
        OBDESceneNode* createSceneNode(OBDESceneNode*);
        
        /**
         * @brief 
         * 
         * @param 
         * @return OBDEMesh* 
         */
        OBDEMesh* createMesh(std::string);
        
        /**
         * @brief 
         * 
         * @param 
         * @param 
         * @return OBDEMesh* 
         */
        OBDEMesh* createMesh(OBDESceneNode*, std::string);
        
        /**
         * @brief 
         * 
         * @param 
         * @return OBDEAnimation* 
         */
        OBDEAnimation* createAnimation(std::string);
        
        /**
         * @brief 
         * 
         * @param 
         * @param 
         * @return OBDEAnimation* 
         */
        OBDEAnimation* createAnimation(OBDESceneNode*, std::string);

        /**
         * @brief Create a Shader Program object
         * 
         * @param a 
         * @param b 
         * @param c 
         * @return OBDEShaderProgram* 
         */
        OBDEShaderProgram *createShaderProgram(std::string, std::string, std::string);

        /**
         * @brief 
         * 
         * @param rec 
         */
        void registerCamera(OBDECamera* rec);

        /**
         * @brief 
         * 
         * @param lightNode 
         */
        void registerLight(OBDELight* lightNode);

        /**
         * @brief 
         * 
         * @param shaderProgram 
         * @param shaderProgram 
         */
        void registerShaderProgram(std::string, OBDEShaderProgram *);

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
        OBDESceneNode* getDefaultLayer();
    private:
        TMatrixCache *matrixCache;

        ResourceManager *REManager;

        TNode* rootNode;

        OBDESceneNode *clSceneNode;
        OBDESceneNode *defaultSceneNode;

        OBDEShaderProgram *currentProgram;

        std::vector<OBDECamera*> cameras;
        std::vector<OBDELight*> lights;
        std::map<std::string, OBDEShaderProgram*> shaderPrograms;

        // OpenGL
	    GLuint vertexArrayID;
        GLuint programID;
};

#endif