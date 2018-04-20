#ifndef OBDSCENENODE_H
#define OBDSCENENODE_H

#include "OBDEntity.h"

#include "Graphics/TTransform.h"

class OBDSceneNode : public OBDEntity {
    public:
        /**
         * @brief 
         * 
         * @param parent 
         */
        OBDSceneNode();

        /**
         * @brief 
         * 
         * @param parent 
         */
        OBDSceneNode(TNode*);

        /**
         * @brief 
         * 
         * @param parent 
         */
        OBDSceneNode(OBDSceneNode*);

        /**
         * @brief 
         * 
         */
        ~OBDSceneNode();

        /**
         * @brief 
         * 
         * @param tX 
         * @param tY 
         * @param tZ 
         */
        void rotate(f32 rX, f32 rY, f32 rZ, f32 angle);

        /**
         * @brief 
         * 
         */
        void scale(f32 sX, f32 sY, f32 sZ);

        /**
         * @brief 
         * 
         */
        void translate(f32 tX, f32 tY, f32 tZ);

        /**
         * @brief Set the Position
         * 
         * @param p 
         */
        void setPosition(glm::vec3 p);

        /**
         * @brief Set the Rotation
         * 
         * @param r 
         * @param angle 
         */
        void setRotation(glm::vec3 r, f32 angle);

        /**
         * @brief Set the Scale
         * 
         * @param s 
         */
        void setScale(glm::vec3 s);

        /**
         * @brief 
         * 
         */
        void addChild(OBDEntity *);

        /**
         * @brief Get the First Node object
         * 
         * @return TNode* 
         */
        TNode *getFirstNode();

    private:
        TNode* rotationNode;
        TNode* translationNode;
        TNode* scaleNode;

        glm::vec3 node_position;
        glm::vec3 node_rotation;
        glm::vec3 node_scale;
};

#endif