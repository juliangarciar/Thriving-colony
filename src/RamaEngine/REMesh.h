#ifndef REMESH_H
#define REMESH_H

#include "RETypes.h"
#include "RESceneNode.h"

#include "ResourceManager/ResourceOBJ.h"
#include "ResourceManager/ResourceMTL.h"

#include "Graphics/TNode.h"
#include "Graphics/TTransform.h"
#include "Graphics/TMesh.h"

class REMesh {
    public:
        /**
         * @brief 
         * 
         * @param  
         * @param 
         * @param 
         */
        REMesh(RESceneNode*, ResourceOBJ *, ResourceMTL *);

        /**
         * @brief 
         * 
         */
        ~REMesh();

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
         * @brief Set the Texture object
         * 
         */
        void setTexture(std::string, REEnums::TextureTypes, ResourceIMG*);

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
        TMesh *getMesh(std::string);
    private:
        TNode* meshNode;
        TNode* rotationNode;
        TNode* translationNode;
        TNode* scaleNode;
        
        std::map<std::string, TMesh*> meshes;
};

#endif