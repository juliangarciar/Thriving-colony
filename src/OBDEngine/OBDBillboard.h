#ifndef OBDBILLBOARD_H
#define OBDBILLBOARD_H

#include "OBDSceneNode.h"
#include "OBDShaderProgram.h"

#include "Graphics/TBillboard.h"

class OBDBillboard {
    public:
        /**
         * @brief 
         * 
         * @param parent
         * @param position
         */
        OBDBillboard(OBDSceneNode*, OBDShaderProgram *sP, glm::vec3, glm::vec2);

        /**
         * @brief 
         * 
         */
        virtual ~OBDBillboard();

        /**
         * @brief 
         * 
         */
        void setPosition(glm::vec3);

        /**
         * @brief 
         * 
         */
        void setColor(OBDColor, OBDColor);

        /**
         * @brief Set the Size object
         * 
         */
        void setSize(glm::vec2);

        /**
         * @brief Set the Wid object
         * 
         */
        void setFrontWidth(f32);

		/**
		 * @brief Set the Active object
		 * @param b
		 */
		void setActive(bool);

        /**
         * @brief 
         * 
         */
        glm::vec3 getPosition();

        /**
         * @brief Get the Height object
         * 
         * @return f32 
         */
        glm::vec2 getSize();

        /**
         * @brief Get the Top width object
         * 
         * @return f32 
         */
        f32 getFrontWidth();

         /**
         * @brief Get the Node object
         * 
         * @return TNode* 
         */
        TNode *getNode();

    private:
        TNode* billboardNode;
};

#endif
