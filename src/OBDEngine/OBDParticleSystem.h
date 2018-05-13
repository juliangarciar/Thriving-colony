#ifndef OBDPARTICLESYSTEM_H
#define OBDPARTICLESYSTEM_H

#include "OBDSceneNode.h"
#include "OBDParticleEmiter.h"

class OBDParticleSystem : public OBDEntity {
    
    public:
        /**
         * @brief 
         * 
         * @param
         */
        OBDParticleSystem(OBDSceneNode*);

        /**
         * @brief 
         * 
         */
        ~OBDParticleSystem();

        /**
         * @brief Set the Particle Size object
         * 
         */
        void setParticleSize(glm::vec2);

        /**
         * @brief 
         * 
         */
        void cleanParticles();
    private:
        TNode* particleSystemNode;

        OBDParticleEmiter emiter;
};

#endif