#ifndef OBDBILLBOARD_H
#define OBDBILLBOARD_H

#include "OBDSceneNode.h"

#include "Graphics/TBillboard.h"

class OBDBillboard {
    public:
        /**
         * @brief 
         * 
         * @param parent
         * @param position
         * @param shaderID
         */
        OBDBillboard(OBDSceneNode*, glm::vec3, GLuint, i32);

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
        void setColor(OBDColor*, OBDColor*);

        /**
         * @brief Set the Size object
         * 
         */
        void setSize(f32, f32, f32);

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
        f32 getHeight();

        /**
         * @brief Get the Top width object
         * 
         * @return f32 
         */
        f32 getTopWidth();

        /**
         * @brief Get the Bottom Width object
         * 
         * @return f32 
         */
        f32 getBottomWidth();

        /**
         * @brief 
         * 
         * @return i32 
         */
        i32 getID();

         /**
         * @brief Get the Node object
         * 
         * @return TNode* 
         */
        TNode *getNode();

    private:
        TNode* billboardNode;
        i32 ID;
};

#endif
