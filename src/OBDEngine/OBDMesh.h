#ifndef OBDMESH_H
#define OBDMESH_H

#include "OBDTypes.h"
#include "OBDSceneNode.h"

#include "ResourceManager/ResourceOBJ.h"
#include "ResourceManager/ResourceMTL.h"

#include "Graphics/TNode.h"
#include "Graphics/TTransform.h"
#include "Graphics/TMesh.h"

class OBDMesh {
    public:
        /**
         * @brief 
         * 
         * @param  
         * @param 
         * @param 
         */
        OBDMesh(OBDSceneNode*, ResourceOBJ *, ResourceMTL *);

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
         * @brief Set the glslTexture object
         * 
         */
        void setTexture(std::string, OBDEnums::TextureTypes, ResourceIMG*);

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
        TMesh *getShape(std::string);

        /**
         * @brief Get the Meshes object
         * 
         * @return std::map<std::string, TMesh*> 
         */
        std::map<std::string, TMesh*> getMeshes();

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
    private:
        TNode* meshNode;
        TNode* rotationNode;
        TNode* translationNode;
        TNode* scaleNode;
        
        std::map<std::string, TMesh*> meshes;

        glm::vec3 node_position;
        glm::vec3 node_rotation;
        glm::vec3 node_scale;
};

#endif