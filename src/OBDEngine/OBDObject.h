#ifndef OBDOBJECT_H
#define OBDOBJECT_H

#include "OBDEntity.h"
#include "OBDMesh.h"
#include "OBDSceneNode.h"

#include "ResourceManager/ResourceOBJ.h"
#include "ResourceManager/ResourceMTL.h"

#include "Graphics/TTransform.h"
#include "Graphics/TMesh.h"

class OBDObject : public OBDEntity {
    public:
        /**
         * @brief Construct a new OBDMesh object
         * 
         * @param obj 
         * @param mtl 
         */
        OBDObject(ResourceOBJ *obj, ResourceMTL *mtl);

        /**
         * @brief Construct a new OBDMesh object
         * 
         * @param parent 
         * @param obj 
         * @param mtl 
         */
        OBDObject(OBDSceneNode* parent, ResourceOBJ *obj, ResourceMTL *mtl);

        /**
         * @brief Destroy the OBDObject object
         * 
         */
        virtual ~OBDObject();

        /**
         * @brief 
         * 
         * @param tX 
         * @param tY 
         * @param tZ 
         */
        void rotate(f32 rX, f32 rY, f32 rZ, f32 angle);

        /**
         * @brief 
         * 
         */
        void scale(f32 sX, f32 sY, f32 sZ);

        /**
         * @brief 
         * 
         */
        void translate(f32 tX, f32 tY, f32 tZ);

        /**
         * @brief Set the Position
         * 
         * @param p 
         */
        void setPosition(glm::vec3 p);

        /**
         * @brief Set the Rotation
         * 
         * @param r 
         * @param angle 
         */
        void setRotation(glm::vec3 r, f32 angle);

        /**
         * @brief Set the Scale
         * 
         * @param s 
         */
        void setScale(glm::vec3 s);

		/**
		 * @brief Get the Position object
		 * 
		 * @return glm::vec3 
		 */
		glm::vec3 getPosition();

		/**
		 * @brief Get the Rotation object
		 * 
		 * @return glm::vec3 
		 */
		glm::vec3 getRotation();

		/**
		 * @brief Get the Scale object
		 * 
		 * @return glm::vec3 
		 */
		glm::vec3 getScale();

        /**
         * @brief Set the Active object
         * 
         * @param a 
         */
        void setActive(bool a);

        /**
         * @brief Get the Active object
         * 
         * @return true 
         * @return false 
         */
        bool getActive();

        /**
         * @brief Set the Material object
         * 
         * @param mtl 
         */
        void setMaterial(ResourceMTL *mtl);

        /**
         * @brief 
         * @param r 
         * @param sync 
         */
        void loadTextures(ResourceManager*, bool);

        /**
         * @brief Get the Mesh Amount object
         * 
         * @return u32 
         */
        u32 getMeshAmount();

        /**
         * @brief Get the Mesh object
         * 
         * @return TMesh* 
         */
        OBDMesh *getMesh(std::string);

        /**
         * @brief Get the Meshes object
         * 
         * @return std::map<std::string, OBDMesh*> 
         */
        std::map<std::string, OBDMesh*> getMeshes();

        /**
         * @brief Get the First Node object
         * 
         * @return TNode* 
         */
        TNode *getFirstNode();

    private:
        TNode* rotationNode;
        TNode* translationNode;
        TNode* scaleNode;

        std::map<std::string, OBDMesh*> meshes;

        glm::vec3 node_position;
        glm::vec3 node_rotation;
        glm::vec3 node_scale;
};

#endif