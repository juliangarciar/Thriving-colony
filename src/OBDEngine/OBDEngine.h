#ifndef RAMAENGINE_H
#define RAMAENGINE_H

#include "OBDTypes.h"
#include "OBDEnums.h"

#include "OBDAnimation.h"
#include "OBDBillboard.h"
#include "OBDCamera.h"
#include "OBDLight.h"
#include "OBDObject.h"
#include "OBDSceneNode.h"
#include "OBDShaderProgram.h"
#include "OBDTerrain.h"
#include "OBDTile.h"
#include "OBDTexture.h"

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
         */
        void draw();

        /**
         * @brief Create a Light object
         * 
         * @param color 
         * @param intensity 
         * @param ambient 
         * @param attenuation 
         * @return OBDLight* 
         */
        OBDLight* createLight(OBDColor color, f32 intensity, f32 ambient, f32 attenuation);

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

		/**
		 * @brief Create a Texture object
		 * 
		 * @return OBDTexture* 
		 */
		OBDTexture *createTexture(OBDEnums::TextureTypes, std::string);

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
		 * @brief Set the Window Size object
		 * @param width
		 * @param height
		 */
		void setWindowSize(i32, i32);

        /**
         * @brief Set the Clean Color object
         * @param color
         */
        void setClearColor(OBDColor);

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

        /**
         * @brief Get World Coordinates From Screen
         * 
         * @return glm::vec3 
         */
        glm::vec3 getWorldCoordinatesFromScreen(glm::vec3);

        /**
         * @brief Get Screen Coordinates From World
         * 
         * @return glm::vec3 
         */
        glm::vec3 getScreenCoordinatesFromWorld(glm::vec3);

        /**
         * @brief Get World Coordinates From Screen
         * 
         * @return glm::vec3 
         */
        OBDLine getRaycastFromScreenCoordinates(glm::vec2);

        /**
         * @brief Get World Coordinates From Screen
         * 
         * @return glm::vec3 
         */
        glm::vec3 getRelativeWorldCoordinatesFromScreen(glm::vec3, glm::mat4);

        /**
         * @brief Get Screen Coordinates From World
         * 
         * @return glm::vec3 
         */
        glm::vec3 getRelativeScreenCoordinatesFromWorld(glm::vec3, glm::mat4);

        /**
         * @brief Get World Coordinates From Screen
         * 
         * @return glm::vec3 
         */
        OBDLine getRelativeRaycastFromScreenCoordinates(glm::vec2, glm::mat4);

		/**
		 * @brief Get the Resource Manager object
		 * 
		 * @return ResourceManager* 
		 */
		ResourceManager *getResourceManager();

        
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

		/////////////////////////////
    private:
        ResourceManager *OBDManager;

        TNode* rootNode;

        OBDSceneNode *clSceneNode;
        OBDSceneNode *defaultSceneNode;

        OBDShaderProgram *currentProgram;

        std::vector<OBDCamera*> cameras;
        std::vector<OBDLight*> lights;
        std::map<std::string, OBDShaderProgram*> shaderPrograms;

		glm::vec4 viewport;

        i32 windowWidth;
        i32 windowHeight;
};

#endif