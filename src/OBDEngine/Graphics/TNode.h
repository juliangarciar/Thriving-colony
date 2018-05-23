#ifndef TNODE_H
#define TNODE_H

#include "TEntity.h"

class TNode {
    public:
        /**
         * @brief Construct a new TNode object
         * 
         */
        TNode();

        /**
         * @brief Construct a new TNode oject and attach a new Entity to it.
         * 
         */
        TNode(TEntity*);

        /**
         * @brief Construct a new TNode object and attach a new Entity to it. After that, give it a parent.
         * 
         * @param TEntity entity for the node
         * @param TNode parent.
         */
        TNode(TEntity*, TNode*);

        /**
         * @brief Destroy the TNode object
         * 
         */
        ~TNode();

        /**
         * @brief add a child to this node's children list.
         * 
         * @param TNode new child
         */
        void addChild(TNode*);

        /**
         * @brief delete a child from this node's children list.
         * 
         * @param TNode node to remove.
         */
        void removeChild(TNode*);

        /**
         * @brief recursively call all children's draw function
         * 
         */
        void draw();

        /**
         * @brief Give this node a new entity
         * 
         * @param TEntity new entity
         */
        void setEntity(TEntity*);

        /**
         * @brief remove this node's entity
         */
        void removeEntity();

        /**
         * @brief Get the Entity of this node
         * 
         * @return TEntity* this node's entity
         */
        TEntity *getEntity();

        /**
         * @brief Set wether or not this node is active. Inactive node's draw function will not be executed.
         * Neither will its children.
         * 
         * @param a active status
         */
        void setActive(bool a);

        /**
         * @brief Get wether or not this node is active.
         * 
         * @return true this node is active
         * @return false this node is inactive
         */
        bool getActive();

        /**
         * @brief Set this node's parent.
         * @param node 
         */
        void setParent(TNode *);

        /**
         * @brief return this node's parent.
         * 
         * @return TNode* parent.
         */
        TNode *getParent();
    private:
        TEntity *entity;
        TNode *parent;
        std::vector<TNode*> children;
        bool active;
};

#endif