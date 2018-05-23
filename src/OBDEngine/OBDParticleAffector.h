#ifndef OBDPARTICLEAFFECTOR_H
#define OBDPARTICLEAFFECTOR_H

#include "OBDSceneNode.h"

#include "Graphics/TParticle.h"

/**
 * @brief The different types of OBDParticleAffector
 * 
 */
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
         * @brief OBDParticleAffector constructor.
         * 
         */
        OBDParticleAffector();

        /**
         * @brief OBDParticleAffector destructor.
         * 
         */
        ~OBDParticleAffector();

        /**
         * @brief This method change the different parameters of the particles that are passed by parameter depending of the type of the OBDParticleAffector.
         * 
         * @param std::vector<TParticle*> will be the particles that are going to be affected by the OBDParticleAffector.
         */
        virtual void affect(std::vector<TParticle*>) = 0;
        
        /**
         * @brief Get the OBDParticleAffector is enabled or not.
         * 
         * @return true when is enabled.
         * @return false when is not enabled.
         */
        bool getEnabled();

        /**
         * @brief Set if the OBDParticleAffector is enabled or not.
         * 
         * @param True when it is going to be enabled and false in other case.
         */
        void setEnabled(bool);

    private:
        bool enabled;
        
        //ParticleAffectorType type;
};

#endif