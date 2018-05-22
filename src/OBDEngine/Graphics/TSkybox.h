#ifndef TSKYBOX_H
#define TSKYBOX_H

#include "TEntity.h"
#include "TCubemapTexture.h"

class TSkybox : public TEntity {
    public:
        /**
         * @brief 
         * 
         */
        TSkybox(GLuint, TCubemapTexture*);

        /**
         * @brief 
         * 
         */
        virtual ~TSkybox();

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
         * @brief Set the Texture object
         * 
         */
        void setTexture(TCubemapTexture*);

    private:
		TCubemapTexture *texture;

		GLuint programID;

        GLuint vpID;
        GLuint skyboxID;
		GLuint vbo_cube_vertices;
		GLuint ibo_cube_indices;
};

#endif