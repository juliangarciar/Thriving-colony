#ifndef TMESH_H
#define TMESH_H

#include "TEntity.h"
#include "TTexture.h"

#include "../OBDMaterial.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

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
        
        GLuint VBOID;
	    GLuint IBOID;

        GLuint lightID;
        GLuint materialID;
        GLuint textureID;
};

#endif