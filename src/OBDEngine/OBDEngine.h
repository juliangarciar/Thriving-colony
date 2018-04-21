#ifndef RAMAENGINE_H
#define RAMAENGINE_H

#include "OBDTypes.h"
#include "OBDEnums.h"
#include "OBDAnimation.h"
#include "OBDBillboard.h"
#include "OBDCamera.h"
#include "OBDLight.h"
#include "OBDMesh.h"
#include "OBDSceneNode.h"
#include "OBDShaderProgram.h"

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
         * @return OBDLight* 
         */
        OBDLight* createLight(OBDColor color, u32 intensity);

        /**
         * @brief 
         * 
         * @return OBDCamera* 
         */
        OBDCamera* createCamera();

        /**
         * @brief 
         * 
         * @return OBDSceneNode* 
         */
        OBDSceneNode* createSceneNode();

        /**
         * @brief 
         * 
         * @param 
         * @return OBDSceneNode* 
         */
        OBDSceneNode* createSceneNode(OBDSceneNode*);
        
        /**
         * @brief 
         * 
         * @param 
         * @return OBDMesh* 
         */
        OBDMesh* createMesh(std::string);
        
        /**
         * @brief 
         * 
         * @param 
         * @param 
         * @return OBDMesh* 
         */
        OBDMesh* createMesh(OBDSceneNode*, std::string);
        
        /**
         * @brief 
         * 
         * @param 
         * @return OBDAnimation* 
         */
        OBDAnimation* createAnimation(std::string);
        
        /**
         * @brief 
         * 
         * @param 
         * @param 
         * @return OBDAnimation* 
         */
        OBDAnimation* createAnimation(OBDSceneNode*, std::string);

        /**
         * @brief Create a Shader Program object
         * 
         * @param a 
         * @param b 
         * @param c 
         * @return OBDShaderProgram* 
         */
        OBDShaderProgram *createShaderProgram(std::string, std::string, std::string);

        /**
         * @brief 
         * 
         * @param rec 
         */
        void registerCamera(OBDCamera* rec);

        /**
         * @brief 
         * 
         * @param lightNode 
         */
        void registerLight(OBDLight* lightNode);

        /**
         * @brief 
         * 
         * @param shaderProgram 
         * @param shaderProgram 
         */
        void registerShaderProgram(std::string, OBDShaderProgram *);

        /**
         * @brief Set the current shader program
         * @param program
         */
        void setCurrentShaderProgram(std::string);

        /**
         * @brief Set the Clean Color object
         * @param color
         */
        void setClearColor(OBDColor);

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
        OBDSceneNode* getDefaultLayer();
    private:
        ResourceManager *OBDManager;

        TNode* rootNode;

        OBDSceneNode *clSceneNode;
        OBDSceneNode *defaultSceneNode;

        OBDShaderProgram *currentProgram;

        std::vector<OBDCamera*> cameras;
        std::vector<OBDLight*> lights;
        std::map<std::string, OBDShaderProgram*> shaderPrograms;
};

#endif