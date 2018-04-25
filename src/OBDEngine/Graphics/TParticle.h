#ifndef TPARTICLE_H
#define TPARTICLE_H

#include <GLFW/glfw3.h>

#include "TEntity.h"

class TParticle : public TEntity {
    
    public:
        TParticle(glm::vec3);

        virtual ~TParticle();

        void beginDraw();

        void endDraw();

    private:
};

#endif