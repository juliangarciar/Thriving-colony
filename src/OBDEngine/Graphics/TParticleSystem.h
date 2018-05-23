#ifndef TPARTICLESYSTEM_H
#define TPARTICLESYSTEM_H

#include "TEntity.h"
#include "TParticle.h"

class TParticleSystem : public TEntity {
    
    public:
        /**
         * @brief TParticleSystem constructor.
         * 
         */
        TParticleSystem();

        /**
         * @brief TParticleSystem destructor.
         * 
         */
        virtual ~TParticleSystem();

        /**
         * @brief Draw the particles.
         * 
         */
        void beginDraw();

        /**
         * @brief End the draw the particles.
         * 
         */
        void endDraw();

        /**
         * @brief Set the particles of the system particle.
         * 
         */
        void setParticles(std::vector<TParticle*>);

        /**
         * @brief Get the particles of the system particle.
         * 
         * @return std::vector<TParticle*> that is going to be the value of particles variable.
         */
        std::vector<TParticle*> getParticles();

    private:
        //Particles of the particle system.
        std::vector<TParticle*> particles;
};

#endif