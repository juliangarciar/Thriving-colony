#ifndef OBDMESH_H
#define OBDMESH_H

#include "OBDEntity.h"
#include "OBDSceneNode.h"

#include "ResourceManager/ResourceOBJ.h"
#include "ResourceManager/ResourceMTL.h"

#include "Graphics/TTransform.h"
#include "Graphics/TMesh.h"

class OBDMesh : public OBDEntity {
    public:
        /**
         * @brief 
         * 
         * @param  
         * @param 
         * @param 
         */
        OBDMesh(ResourceMesh, ResourceMaterial);

        /**
         * @brief 
         * 
         * @param  
         * @param 
         * @param 
         */
        OBDMesh(OBDSceneNode*, ResourceMesh, ResourceMaterial);

        /**
         * @brief 
         * 
         */
        ~OBDMesh();

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
         * @brief Set the ResourceMaterial object
         * 
         */
        void setMaterial(ResourceMaterial);

        /**
         * @brief Set the glslTexture object
         * 
         */
        void setTexture(OBDEnums::TextureTypes, ResourceIMG*);

        /**
         * @brief 
         * 
         * @param i 
         */
        void setID(GLuint i);

        /**
         * @brief 
         * 
         * @return GLuint 
         */
        GLuint getID();

        /**
         * @brief Set the Name object
         * 
         * @param n 
         */
        void setName(std::string n);

        /**
         * @brief Get the Name object
         * 
         * @return std::string 
         */
        std::string getName();

        /**
         * @brief Set the Name object
         * 
         * @param n 
         */
        void setMaterialName(std::string n);

        /**
         * @brief Get the Name object
         * 
         * @return std::string 
         */
        std::string getMaterialName();

        /**
         * @brief 
         * @param
         * @param sync
         */
        void loadTextures(ResourceManager*, bool);
        
        /**
         * @brief 
         * 
         * @return TMesh* 
         */
        TMesh* getMeshEntity();

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
        TNode* meshNode;

        glm::vec3 node_position;
        glm::vec3 node_rotation;
        glm::vec3 node_scale;

        GLuint ID;
        std::string name;
        std::string materialName;

        ResourceMesh mesh;
        ResourceMaterial material;
};

#endif