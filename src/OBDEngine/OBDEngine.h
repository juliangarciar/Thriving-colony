#ifndef RAMAENGINE_H
#define RAMAENGINE_H

#include "OBDTypes.h"
#include "OBDEnums.h"

#include "OBDAnimation.h"
#include "OBDBillboard.h"
#include "OBDSkybox.h"
#include "OBDCamera.h"
#include "OBDLight.h"
#include "OBDObject.h"
#include "OBDSceneNode.h"
#include "OBDShaderProgram.h"
#include "OBDTerrain.h"
#include "OBDTile.h"

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
         * @param screenWidth 
         * @param screenHeight 
         */
        void Init(i32 screenWidth, i32 screenHeight);

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
         * @param autoload
         * @return OBDMesh* 
         */
        OBDObject* createObject(std::string, bool = false);
        
        /**
         * @brief 
         * 
         * @param 
         * @param 
         * @param autoload
         * @return OBDMesh* 
         */
        OBDObject* createObject(OBDSceneNode*, std::string, bool = false);

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
		 * @brief Create a Terrain object
		 * @param terrain path
		 * @return OBDTerrain* 
		 */
		OBDTerrain *createTerrain(std::string);

		/**
		 * @brief Create a Terrain object
		 * @param terrain path
		 * @return OBDTerrain* 
		 */
		OBDTerrain *createTerrain(OBDSceneNode*, std::string);
        
		////////////SANDBOX////////////

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
		 * @brief Julian, genera comentarios, primer aviso xD
		 * 
		 * @param _texture 
		 * @param _position 
		 * @return OBDTile* 
		 */
        OBDTile* createTile(ResourceIMG* _texture, glm::vec2 _position);

        /**
         * @brief
         * @param a 
         * @param b 
         * @param c 
         */
        OBDBillboard* createBillboard(OBDSceneNode*, i32, glm::vec3);

        /**
         * @brief Create a Skybox object
         * 
         * @param texture 
         * @return OBDSkybox* 
         */
        OBDSkybox* createSkybox(TTexture* texture);

		/////////////////////////////

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

        i32 screenWidth;
        i32 screenHeight;
};

#endif