#ifndef RAMAENGINE_H
#define RAMAENGINE_H

#include "OBDTypes.h"
#include "OBDEnums.h"

#include "OBDAnimation.h"
#include "OBDBillboard.h"
#include "OBDCamera.h"
#include "OBDColor.h"
#include "OBDLight.h"
#include "OBDMaterial.h"
#include "OBDObject.h"
#include "OBDSceneNode.h"
#include "OBDShaderProgram.h"
#include "OBDSkybox.h"
#include "OBDTerrain.h"
#include "OBDTexture.h"
#include "OBDVideo.h"

#include "ResourceManager/ResourceManager.h"
#include "Graphics/TNode.h"
#include "Graphics/TShaderSwapper.h"

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

#ifdef USEVIDEO
		/**
		 * @brief 
		 * 
		 */
		void InitVideoSystem();
#endif

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
        OBDCamera* createCamera(f32 far, f32 fov);
        
        /**
         * @brief 
         * 
         * @param
         * @return OBDMesh* 
         */
        OBDObject* createObject(u32, std::string, bool);
        
        /**
         * @brief 
         * 
         * @param 
         * @param 
         * @return OBDMesh* 
         */
        OBDObject* createObject(OBDSceneNode*, u32, std::string, bool);

        /**
         * @brief 
         * 
         * @param vector of objects
         * @param material
         * @param autoload
         * @return OBDAnimation* 
         */
        OBDAnimation* createAnimation(std::vector<std::string>, std::string, bool);
        
        /**
         * @brief 
         * 
         * @param parent
         * @param vector of objects
         * @param material
         * @param autoload
         * @return OBDAnimation* 
         */
        OBDAnimation* createAnimation(OBDSceneNode*, std::vector<std::string>, std::string, bool);

		/**
		 * @brief Create a Terrain object
		 * @param terrain path
		 * @return OBDTerrain* 
		 */
		OBDTerrain *createTerrain(std::string, f32 y_offset, f32 y_scale, i32 step);

		/**
		 * @brief Create a Terrain object
		 * @param terrain path
		 * @return OBDTerrain* 
		 */
		OBDTerrain *createTerrain(OBDSceneNode*, std::string, f32 y_offset, f32 y_scale, i32 step);

        /**
         * @brief
         * @param a 
         * @param c 
         */
        OBDBillboard* createBillboard(OBDSceneNode*, OBDShaderProgram *, glm::vec3, glm::vec2);
#ifdef USEVIDEO
        /**
         * @brief
         * @param a 
         * @param c 
         */
        OBDVideo* createVideo(OBDSceneNode*, OBDShaderProgram *, std::string);
#endif
        /**
         * @brief Create a Skybox object
         * 
         * @param texture 
         * @return OBDSkybox* 
         */
        OBDSkybox* createSkybox(OBDSceneNode*, OBDShaderProgram*, std::vector<std::string>);

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
		 * @brief Create a Material object
		 * @path
		 * @name
		 * @return OBDMaterial* 
		 */
		OBDMaterial *createMaterial(std::string, std::string);

		/**
		 * @brief Create a Texture object
		 * 
		 * @return OBDTexture* 
		 */
		OBDTexture *createTexture(OBDEnums::TextureTypes, std::string);

		/**
		 * @brief Create a Overall Scene Node object
		 * 
		 * @return OBDSceneNode* 
		 */
		OBDSceneNode* createShaderedSceneNode(std::string sN, std::string vs, std::string fs);

		/**
		 * @brief Create a Overall Scene Node object
		 * 
		 * @return OBDSceneNode* 
		 */
		OBDSceneNode* createShaderedSceneNode(OBDSceneNode *p, std::string sN, std::string vs, std::string fs);

        /**
         * @brief 
         * @param r 
         * @param sync 
         */
        void loadObjectTexturesFromMTL(OBDObject *, ResourceMTL *m, bool = true);

        /**
         * @brief 
         * @param r 
         * @param sync 
         */
        void loadAnimationTexturesFromMTL(OBDAnimation *, ResourceMTL *m, bool = true);

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
		 * @brief Get the Resource Manager object
		 * 
		 * @return ResourceManager* 
		 */
		ResourceManager *getResourceManager();

		/**
		 * @brief Get the Shader Program object
		 * 
		 * @return OBDShaderProgram* 
		 */
		OBDShaderProgram *getRegisteredShaderProgram(std::string);
    private:
        ResourceManager *OBDManager;

        TNode* rootNode;

        OBDSceneNode *clSceneNode;
        OBDSceneNode *defaultSceneNode;

        std::vector<OBDCamera*> cameras;
        std::vector<OBDLight*> lights;

        std::map<std::string, OBDShaderProgram*> shaderPrograms;

		glm::vec4 viewport;

        i32 windowWidth;
        i32 windowHeight;
};

#endif