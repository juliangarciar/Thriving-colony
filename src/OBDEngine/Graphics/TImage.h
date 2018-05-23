#ifndef TIMAGE_H
#define TIMAGE_H

#include "TEntity.h"
#include "../ResourceManager/ResourceIMG.h"

class TImage : public TEntity {
    public:
        /**
         * @brief 
         * 
         */
        TImage(GLuint programID, ResourceIMG *);

        /**
         * @brief 
         * 
         */
        ~TImage();

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
	private:
		ResourceIMG *data;

		GLuint programID;

		GLuint textureID;
		GLuint mvpID;

		GLuint VAO;
		GLuint vert_buf;
		GLuint uv_buf;
		GLuint elem_buf;
		
		glm::mat4 mvp;
};

#endif