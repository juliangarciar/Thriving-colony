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
        void rotate(f32 rX, f32 rY, f32 rZ);

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
         * @brief 
         * 
         */
        void setPosition(glm::vec3 p);

        /**
         * @brief 
         * 
         */
        void setRotation(glm::vec3 r);

        /**
         * @brief 
         * 
         */
        void setScale(glm::vec3 s);

        void setActive(bool a);

        bool getActive();

        void setName(std::string n);

        std::string getName();

        void setID(GLuint i);

        GLuint getID();
    private:
        TNode* meshNode;
        TNode* rotationNode;
        TNode* translationNode;
        TNode* scaleNode;
        
        std::map<std::string, TMesh*> meshes;
};

#endif