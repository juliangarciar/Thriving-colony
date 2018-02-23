#ifndef REMESH_H
#define REMESH_H

#include <vector>
#include <algorithm>
#include <Types.h>
#include "TNode.h"
#include "TMesh.h"
#include "TTransform.h"



class REMesh {
    public:
        /**
         * @brief 
         * 
         * @param parent 
         */
        REMesh(TNode* parent);

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

        TNode* meshNode, rotationNode, translationNode, scaleNode;
        
};

#endif