#ifndef TANIMATION_H
#define TANIMATION_H

#include "TEntity.h"
#include "TMesh.h"

class TAnimation : public TEntity {
    public:
        /**
         * @brief constructs a new animation entity to be used on a node.
         * 
         */
        TAnimation();

        /**
         * @brief Destructor for an animation entity.
         * 
         */
        virtual ~TAnimation();

        /**
         * @brief 
         * 
         */
        void beginDraw();
        
        /**
         * @brief 
         * 
         */
        void endDraw();

        /**
         * @brief 
         * 
         */
        void setAnimation(TMesh);
    private:
        std::vector<TMesh> animation;
};

#endif