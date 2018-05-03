#ifndef OBDPARTICLEAFFECTOR_H
#define OBDPARTICLEAFFECTOR_H

#include "OBDSceneNode.h"

#include "Graphics/TParticle.h"

enum ParticleAffectorType {
    Attract,
    FadeOut,
    Gravity,
    Rotate,
    Scale,
    Count
};

class OBDParticleAffector {
    
    public:
        /**
         * @brief 
         * 
         */
        OBDParticleAffector();

        /**
         * @brief 
         * 
         */
        ~OBDParticleAffector();

        /**
         * @brief 
         * 
         */
        virtual void affect(i32, std::vector<TParticle*>) = 0;
        
        /**
         * @brief Get the Enabled object
         * 
         * @return true 
         * @return false 
         */
        bool getEnabled();

        /**
         * @brief Set the Enabled object
         * 
         */
        void setEnabled(bool);

    private:
        bool enabled;
        
        ParticleAffectorType type;
};

#endif