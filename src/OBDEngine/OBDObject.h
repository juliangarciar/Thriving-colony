#ifndef OBDMESH_H
#define OBDMESH_H

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


        //std::map<std::string, TMesh*> meshes;