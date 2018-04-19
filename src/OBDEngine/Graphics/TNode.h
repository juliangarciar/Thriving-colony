#ifndef TNODE_H
#define TNODE_H

#include "TEntity.h"

class TNode {
    public:
        /**
         * @brief 
         * 
         */
        TNode();

        /**
         * @brief 
         * 
         * @param TEntity 
         */
        TNode(TEntity*);

        /**
         * @brief 
         * 
         * @param TEntity 
         * @param TNode 
         */
        TNode(TEntity*, TNode*);

        /**
         * @brief 
         * 
         */
        ~TNode();

        /**
         * @brief 
         * 
         * @param TNode 
         */
        void addChild(TNode*);

        /**
         * @brief 
         * 
         * @param TNode 
         */
        void removeChild(TNode*);

        /**
         * @brief 
         * 
         */
        void draw();

        /**
         * @brief 
         * 
         * @param TEntity 
         */
        void setEntity(TEntity*);

        /**
         * @brief 
         */
        void removeEntity();

        /**
         * @brief 
         * 
         * @return TEntity* 
         */
        TEntity *getEntity();

        /**
         * @brief Set if Active
         * 
         * @param a 
         */
        void setActive(bool a);

        /**
         * @brief Get if Active
         * 
         * @return true 
         * @return false 
         */
        bool getActive();

        /**
         * @brief 
         * 
         * @return TNode* 
         */
        TNode *getParent();
    private:
        TEntity *entity;
        TNode *parent;
        std::vector<TNode*> children;
        bool active;
};

#endif