#ifndef REMESH_H
#define REMESH_H

#include "RETypes.h"
#include "RESceneNode.h"

#include "ResourceManager/ResourceOBJ.h"

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
         */
        REMesh(RESceneNode*, ResourceOBJ *);

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

    private:
        TNode* meshNode;
        TNode* rotationNode;
        TNode* translationNode;
        TNode* scaleNode;
        
};

#endif