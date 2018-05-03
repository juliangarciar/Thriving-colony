#ifndef OBDPARTICLEEMITER_H
#define OBDPARTICLEEMITER_H

#include "OBDSceneNode.h"

#include "Graphics/TParticle.h"

enum ParticleEmiterType {
    Point
};

class OBDParticleEmiter {
    
    public:
        /**
         * @brief 
         * 
         */
        OBDParticleEmiter();

        /**
         * @brief 
         * 
         * @param parent 
         */
        OBDParticleEmiter(i32, i32, std::vector<TParticle*>);

        /**
         * @brief 
         * 
         */
        ~OBDParticleEmiter();

        /**
         * @brief Get the Type object
         * 
         * @return ParticleEmiterType 
         */
        virtual ParticleEmiterType getType() {return ParticleEmiterType::Point;};

    private:
        ParticleEmiterType type;
};

#endif