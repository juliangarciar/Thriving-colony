#ifndef TSKYBOX_H
#define TSKYBOX_H

#include "TEntity.h"
#include "TCubemapTexture.h"

class TSkybox : public TEntity {
    public:
        /**
         * @brief Construct a new TSkybox object
         * 
         * 
         * @param id
         * @param cube texture
         */
        TSkybox(GLuint, TCubemapTexture*);

        /**
         * @brief Destroy the TSkybox object
         * 
         */
        virtual ~TSkybox();

        /**
         * @brief draw the skybox
         * 
         */
        void beginDraw();

        /**
         * @brief free buffers
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
        // buffers
		GLuint VAO;
		GLuint vbo_cube_vertices;
		GLuint ibo_cube_indices;
};

#endif