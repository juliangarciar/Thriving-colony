#ifndef OBDBILLBOARD_H
#define OBDBILLBOARD_H

#include "OBDSceneNode.h"

#include "Graphics/TBillboard.h"

class OBDBillboard : public OBDEntity {
    
    public:
        /**
         * @brief 
         * 
         */
        OBDBillboard();

        /**
         * @brief 
         * 
         * @param parent 
         */
        OBDBillboard(OBDSceneNode*, i32, glm::vec3, GLuint);

        /**
         * @brief 
         * 
         */
        ~OBDBillboard();

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
          * @brief Set the Bottom Width object
          * 
          */
        void setBottomWidth(f32);

        /**
         * @brief 
         * 
         */
        glm::vec3 getPosition();

        /**
         * @brief 
         * 
         */
        i32 getID();

        /**
         * @brief 
         * 
         */
        OBDColor* getTopColor();

        /**
         * @brief
         */
        OBDColor* getBottomColor();

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
         * @brief Get the First Node object
         * 
         * @return TNode* 
         */
        TNode *getFirstNode();

    private:
        TNode* billboardNode;
        TNode* rotationNode;
        TNode* translationNode;
        TNode* scaleNode;
        i32 ID;
};

#endif
