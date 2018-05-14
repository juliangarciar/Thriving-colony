#ifndef TMESH_H
#define TMESH_H

#include "TEntity.h"
#include "TTexture.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

class TMesh : public TEntity {
    public:
        /**
         * @brief 
         * 
         */
        TMesh(glslMesh*, glslMaterial*);

        /**
         * @brief 
         * 
         */
        ~TMesh();

        /**
         * @brief 
         * 
         */
        virtual void beginDraw();

        /**
         * @brief 
         * 
         */
        virtual void endDraw();

        /**
         * @brief Set the Material object
         * 
         * @param m 
         */
        virtual void setMaterial(glslMaterial *m);

        /**
         * @brief Set the glslTexture object
         * 
         */
        virtual void setTexture(OBDEnums::TextureTypes, TTexture*);
    private:
        glslMesh *mesh;
        glslMaterial *material; //¿?
        glslTexture activeTextures;
        
        std::vector<TTexture*> textures;

		glm::mat4 modelMatrix;
        
        GLuint VBOID;
	    GLuint IBOID;

        GLuint lightID;
        GLuint materialID;
        GLuint textureID;
};

#endif