#ifndef TMESH_H
#define TMESH_H

#include <GL/glew.h>

#include "TEntity.h"
#include "../ResourceManager/Helpers/ResourceMesh.h"
#include "../ResourceManager/Helpers/ResourceMaterial.h"
#include "TTexture.h"

#define BUFFER_OFFSET(i) ((char *)nullptr + (i))

class TMesh : public TEntity {
    public:
        /**
         * @brief 
         * 
         */
        TMesh(ResourceMesh *, ResourceMaterial *);

        /**
         * @brief 
         * 
         */
        virtual ~TMesh();

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
         * @brief Set the glslTexture object
         * 
         */
        virtual void setTexture(OBDEnums::TextureTypes, TTexture*);

        /**
         * @brief Get the Mesh object
         * 
         * @return ResourceMesh* 
         */
        ResourceMesh* getMesh();

        /**
         * @brief Get the glslMaterial object
         * 
         * @return ResourceMaterial* 
         */
        ResourceMaterial* getMaterial();
    private:
        ResourceMesh* mesh;
        ResourceMaterial* material;
        
        std::vector<TTexture*> textures;
        
        glslTexture activeTextures;
	    glslMaterial currentMaterial;
        
        GLuint VBOID;
	    GLuint IBOID;

        GLuint lightID;
        GLuint materialID;
        GLuint textureID;
};

#endif