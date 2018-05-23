#ifndef TMESH_H
#define TMESH_H

#include "TEntity.h"

#include "../OBDMaterial.h"

class TMesh : public TEntity {
    public:
        /**
         * @brief 
         * 
         */
        TMesh(glslMesh*, OBDMaterial*);

        /**
         * @brief 
         * 
         */
        ~TMesh();

        /**
         * @brief 
         * 
         */
        void beginDraw();

        /**
         * @brief 
         * 
         */
        void endDraw();

        /**
         * @brief Set the Material object
         * 
         * @param m 
         */
        void setMaterial(OBDMaterial *m);

        /**
         * @brief Set the Material object
         * 
         * @param m 
         */
        OBDMaterial *getMaterial();
    private:
        glslMesh *mesh;
        OBDMaterial *material;

		glm::mat4 modelMatrix;
        
        GLuint materialID;
        GLuint textureID;
};

#endif