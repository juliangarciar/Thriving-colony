#ifndef RAMAENGINE_H
#define RAMAENGINE_H

#include "OBDTypes.h"
#include "OBDEnums.h"

#include "OBDAnimation.h"
#include "OBDBillboard.h"
#include "OBDCamera.h"
#include "OBDColor.h"
#include "OBDImage.h"
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
         * @brief Construct a new OBDEngine object
         * 
         */
        OBDEngine();

        /**
         * @brief Destroy the OBDEngine object
         * 
         */
        ~OBDEngine();

        /**
         * @brief initialize the engine
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
         * @brief draw the scene
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
         * @brief create a new scenenode
         * 
         * @return OBDSceneNode* new scenenode
         */
        OBDSceneNode* createSceneNode();

        /**
         * @brief create a new scene node under the chosen parent.
         * 
         * @param parent
         * @return OBDSceneNode* new scenenode
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
         * @brief Create a Camera object
         * 
         * @param far 
         * @param fov 
         * @return OBDCamera* 
         */
        OBDCamera* createCamera(f32 far, f32 fov);
        
        /**
         * @brief Create a 3d Object 
         * 
         * @param id
         * @param path
         * @param wether or not it should automatically.
         * @return OBDObject* 
         */
        OBDObject* createObject(u32, std::string, bool);
        
        /**
         * @brief create a 3d object
         * 
         * @param parent
         * @param id
         * @param path
         * @param wether or not it should load automatically
         * @return OBDMesh* 
         */
        OBDObject* createObject(OBDSceneNode*, u32, std::string, bool);

        /**
         * @brief create a new animation
         * 
         * @param vector of objects
         * @param material
         * @param autoload
         * @return OBDAnimation* 
         */
        OBDAnimation* createAnimation(std::vector<std::string>, std::string, bool);
        
        /**
         * @brief create a new animation
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
         * @brief create a new billboard
         * @param a 
         * @param c 
         */
        OBDBillboard* createBillboard(OBDSceneNode*, OBDShaderProgram *, glm::vec3, glm::vec2);

#ifdef USEVIDEO
        /**
         * @brief create a new video
         * @param  parent
         * @param  shader
         * @param  path
         */
        OBDVideo* createVideo(OBDSceneNode*, OBDShaderProgram *, std::string);
#endif

        /**
         * @brief create a new image
         * 
         * @param parent
         * @param shader
         * @param path
         */
        OBDImage* createImage(OBDSceneNode*, OBDShaderProgram *, std::string);

        /**
         * @brief Create a Skybox object
         * 
         * @param texture 
         * @return OBDSkybox* new skybox
         */
        OBDSkybox* createSkybox(OBDSceneNode*, OBDShaderProgram*, std::vector<std::string>);

        /**
         * @brief Create a Shader Program object
         * 
         * @param path
         * @param fragment shader
         * @param vertex shader
         * @return OBDShaderProgram* 
         */
        OBDShaderProgram *createShaderProgram(std::string, std::string, std::string);

		/**
		 * @brief Create a Material object
		 * @path
		 * @name
		 * @return OBDMaterial* new material
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
         * @brief load a material from an object
         * 
         * @param object
         * @param mtl file
         * @param wether or this shoudl be loaded synchronoulsy or asynchronously
         */
        void loadObjectTexturesFromMTL(OBDObject *, ResourceMTL *m, bool = true);

        /**
         * @brief load a material from an animation
         * 
         * @param object
         * @param mtl file
         * @param wether or this shoudl be loaded synchronoulsy or asynchronously
         */
        void loadAnimationTexturesFromMTL(OBDAnimation *, ResourceMTL *m, bool = true);

        /**
         * @brief add a camera to the register of cameras
         * 
         * @param rec camera to register
         */
        void registerCamera(OBDCamera* rec);

        /**
         * @brief add a light to the register of lights
         * 
         * @param lightNode 
         */
        void registerLight(OBDLight* lightNode);

        /**
         * @brief add a shader to the register of shaders
         * 
         * @param shader name
         * @param shaderProgram shader 
         */
        void registerShaderProgram(std::string, OBDShaderProgram *);

        /**
         * @brief Set the current shader program to use
         * @param program
         */
        void setCurrentShaderProgram(std::string);

		/**
		 * @brief Set the Window Size
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
         * @brief get the root of the tree
         * 
         * @return TNode* 
         */
        TNode* getRootNode();

        /**
         * @brief returns the default scenenode
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
        //Root
        TNode* rootNode;

        // Default layers/scenenodes
        OBDSceneNode *clSceneNode;
        OBDSceneNode *defaultSceneNode;

        // Registers
        std::vector<OBDCamera*> cameras;
        std::vector<OBDLight*> lights;

        std::map<std::string, OBDShaderProgram*> shaderPrograms;

		glm::vec4 viewport;

        i32 windowWidth;
        i32 windowHeight;
};

#endif