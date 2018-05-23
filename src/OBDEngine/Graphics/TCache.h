#ifndef TCACHE_H
#define TCACHE_H

#include "../OBDTypes.h"
#include "../OBDEnums.h"

class TCache {
    public:
        /**
         * @brief Construct a new TCache object
         * 
         */
        TCache();

        /**
         * @brief Destroy the TCache object
         * 
         */
        ~TCache();

        /**
         * @brief 
         * 
         * @param a 
         * @return std::vector<GLuint> 
         */
        std::vector<GLuint> generateAllIDs(GLuint);

        /**
         * @brief Set the All I Ds object
         * 
         * @param a 
         */
        void setAllIDs(std::vector<GLuint>);

        /**
         * @brief 
         * 
         * @param a 
         * @param b 
         */
        void setID(OBDEnums::OpenGLIDs, GLuint);

        /**
         * @brief 
         * 
         * @param a 
         * @return GLuint 
         */
        GLuint getID(OBDEnums::OpenGLIDs);

        /**
         * @brief Set the View Matrix object
         * 
         * @param a 
         */
        void setViewMatrix(glm::mat4);

        /**
         * @brief Get the View Matrix object
         * 
         * @return glm::mat4 
         */
        glm::mat4 *getViewMatrix();

        /**
         * @brief Set the Projection Matrix object
         * 
         * @param a 
         */
        void setProjectionMatrix(glm::mat4);

        /**
         * @brief Get the Projection Matrix object
         * 
         * @return glm::mat4 
         */
        glm::mat4 *getProjectionMatrix();

        /**
         * @brief Set the Camera Position
         * 
         * @param a 
         */
        void setCameraPosition(glm::vec3);

        /**
         * @brief Get the Camera Position
         * 
         * @return glm::vec3 
         */
        glm::vec3 getCameraPosition();

		/**
		 * @brief Get the Lights Buffer object
		 * 
		 * @return GLuint 
		 */
		GLuint getLightsBuffer();

        /**
         * @brief Get the Lights object
         * 
         * @return std::vector<glslLight>* 
         */
        std::vector<glslLight> *getLights();

        /**
         * @brief Get the Matrix Stack object
         * 
         * @return std::stack<glm::mat4>& 
         */
        std::stack<glm::mat4>& getMatrixStack();

		/**
		 * @brief Set the Screen Size object
		 * 
		 */
		void setScreenSize(glm::vec2);

		/**
		 * @brief Get the Screen Size object
		 * 
		 * @return glm::vec2 
		 */
		glm::vec2 getScreenSize();
    private:
        
        std::stack<glm::mat4> matrixStack;

        std::vector<GLuint> parameterIDs;

        glm::mat4 viewMatrix;
        glm::mat4 projectionMatrix;
		glm::vec3 cameraPosition;

		glm::vec2 screenSize;

		GLuint lightsID;
        std::vector<glslLight> *lights;
};

#endif