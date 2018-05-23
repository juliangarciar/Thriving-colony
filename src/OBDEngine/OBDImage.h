#ifndef OBDIMAGE_H
#define OBDIMAGE_H

#include "OBDEntity.h"
#include "OBDSceneNode.h"
#include "OBDShaderProgram.h"

#include "Graphics/TImage.h"

class OBDImage {
    public:
        /**
         * @brief Construct a new OBDImage object
         * 
         * @param parent
         * @param sp
         * @param img
         */
        OBDImage(OBDSceneNode* parent, OBDShaderProgram *, ResourceIMG *);

        /**
         * @brief Destroy the OBDImage object
         * 
         */
        virtual ~OBDImage();

        /**
         * @brief Set the Position object
         * 
         * @param p 
         */
        void setPosition(glm::vec3 p);

        /**
         * @brief set the light to active or inactive
         * 
         * @param bool new light active state
         */
        void setActive(bool);

        /**
         * @brief Get the Position object
         * 
         * @return glm::vec3 
         */
        glm::vec3 getPosition();

        /**
         * @brief returns wether or not the light is active
         * 
         * @return true if the light is active
         * @return false otherwise
         */
        bool getActive();

    private:
        TNode* imageNode;
};

#endif