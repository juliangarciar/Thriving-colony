#ifndef TMESH_H
#define TMESH_H

#include <GL/glew.h>

#include "TEntity.h"
#include "../ResourceManager/Helpers/ResourceMesh.h"
#include "../ResourceManager/Helpers/ResourceMaterial.h"
#include "TTexture.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

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
         * @brief Set the Texture object
         * 
         */
        virtual void setTexture(REEnums::TextureTypes, TTexture*);

        /**
         * @brief Get the Mesh object
         * 
         * @return ResourceMesh* 
         */
        ResourceMesh* getMesh();

        /**
         * @brief Get the Material object
         * 
         * @return ResourceMaterial* 
         */
        ResourceMaterial* getMaterial();
    private:
        ResourceMesh* mesh;
        ResourceMaterial* material;
        
        std::vector<TTexture*> textures;
        
        Texture activeTextures;
        
        GLuint VBOID;
	    GLuint IBOID;

        GLuint lightID;
        GLuint materialID;
        GLuint textureID;
};

#endif