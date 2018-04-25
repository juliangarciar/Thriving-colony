#ifndef TCACHE_H
#define TCACHE_H

#include <GLFW/glfw3.h>

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
        glm::mat4 getViewMatrix();

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
        glm::mat4 getProjectionMatrix();

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
    private:
        std::stack<glm::mat4> matrixStack;

        std::vector<GLuint> parameterIDs;

        glm::mat4 viewMatrix;
        glm::mat4 projectionMatrix;

        std::vector<glslLight> *lights;
};

#endif