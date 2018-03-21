#ifndef TMESH_H
#define TMESH_H

#include <GL/gl.h>

#include "TEntity.h"
#include "../ResourceManager/Helpers/ResourceMesh.h"
#include "../ResourceManager/Helpers/ResourceMaterial.h"
#include "TTexture.h"

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
        virtual void setTexture(OBDEEnums::TextureTypes, TTexture*);

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
        std::map<OBDEEnums::TextureTypes, TTexture*> textures;

        GLuint vertexbuffer;
        GLuint normalbuffer;
        GLuint uvbuffer;
	    GLuint elementbuffer;
};

#endif