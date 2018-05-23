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

		/**
		 * @brief Set the Position object
		 * 
		 * @param position 
		 */
		void setPosition(glm::vec3 position);

		/**
		 * @brief Get the Position object
		 * 
		 * @return glm::vec3 
		 */
		glm::vec3 getPosition();
	private:
		ResourceIMG *data;

		GLuint programID;

		GLuint textureID;
		GLuint mvpID;

		GLuint VAO;
		GLuint vert_buf;
		GLuint uv_buf;
		GLuint elem_buf;

		glm::vec4 position;
		glm::vec2 ratio;
		glm::mat4 vp;
		glm::mat4 m;
};

#endif