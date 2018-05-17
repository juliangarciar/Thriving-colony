#ifndef TPARTICLESYSTEM_H
#define TPARTICLESYSTEM_H

#include "TEntity.h"
#include "TParticle.h"

class TParticleSystem : public TEntity {
    
    public:
        TParticleSystem();

        virtual ~TParticleSystem();

        void beginDraw();
        void endDraw();

        void setParticles(std::vector<TParticle*>);
        std::vector<TParticle*> getParticles();

    private:
        std::vector<TParticle*> particles;
};

#endif