#ifndef TIMAGE_H
#define TIMAGE_H

#include "TEntity.h"
#include "../ResourceManager/ResourceIMG.h"

class TImage : public TEntity {
    public:
        /**
         * @brief Construct a new TImage object
         * 
         * @param programID shader to use to render this image.
         */
        TImage(GLuint programID, ResourceIMG *);

        /**
         * @brief Destroy the TImage object.
         * 
         */
        ~TImage();

        /**
         * @brief render the image on screen.
         * 
         */
        void beginDraw();

        /**
         * @brief free the buffer off the textures.
         * 
         */
        void endDraw();

		/**
		 * @brief Set the Position object
		 * 
		 * @param new position.
		 */
		void setPosition(glm::vec3 position);

		/**
		 * @brief Get the Position object
		 * 
		 * @return glm::vec3 image position.
		 */
		glm::vec3 getPosition();
	private:
		ResourceIMG *data;

		GLuint programID;

		GLuint textureID;
		GLuint mvpID;
		GLuint positionID;

		GLuint VAO;
		GLuint vert_buf;
		GLuint uv_buf;
		GLuint elem_buf;
		
		glm::vec4 position;
		glm::mat4 mvp;
};

#endif