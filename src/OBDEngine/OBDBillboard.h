#ifndef OBDBILLBOARD_H
#define OBDBILLBOARD_H

#include "OBDSceneNode.h"
#include "OBDShaderProgram.h"

#include "Graphics/TBillboard.h"

class OBDBillboard {
    public:
        /**
         * @brief Construct a new OBDBillboard object.
         * 
         * @param parent node.
         * @param sP billboard shader to use to render this.
         * @param position 
         * @param size
         */
        OBDBillboard(OBDSceneNode*, OBDShaderProgram *sP, glm::vec3, glm::vec2);

        /**
         * @brief Destroy the OBDBillboard object
         * 
         */
        virtual ~OBDBillboard();

        /**
         * @brief Set this billboards position
         * 
         */
        void setPosition(glm::vec3);

        /**
         * @brief Set the Color for this billboard's back side
         * 
         */
        void setColor(OBDColor);

        /**
         * @brief Set the Color for this billboard's front side
         * 
         */
        void setFrontColor(OBDColor);

        /**
         * @brief Set the Size of the billboard
         * 
         */
        void setSize(glm::vec2);

        /**
         * @brief Set the Width of the billboard
         * 
         */
        void setFrontWidth(f32);

		/**
		 * @brief Set wether or not this billboard is active
		 * @param b new active status
		 */
		void setActive(bool);

        /**
         * @brief return this billboards position
         * 
         */
        glm::vec3 getPosition();

        /**
         * @brief Get the Height of this billboard
         * 
         * @return f32 billboard's height
         */
        glm::vec2 getSize();

        /**
         * @brief Get the width of the front side.
         * 
         * @return f32 front width
         */
        f32 getFrontWidth();

         /**
         * @brief Get the Node object
         * 
         * @return TNode* node
         */
        TNode *getNode();

    private:
        TNode* billboardNode;
};

#endif
