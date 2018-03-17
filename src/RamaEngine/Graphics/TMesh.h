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

    private:
        ResourceMesh* mesh;
        ResourceMaterial* material;
        std::map<REEnums::TextureTypes, TTexture*> textures;

        GLuint vertexbuffer;
        GLuint normalbuffer;
        GLuint uvbuffer;
	    GLuint elementbuffer;
};

#endif