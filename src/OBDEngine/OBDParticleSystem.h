#ifndef OBDPARTICLESYSTEM_H
#define OBDPARTICLESYSTEM_H

#include "OBDSceneNode.h"
#include "OBDParticleEmiter.h"
#include "OBDParticleAffector.h"

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
         * @brief 
         * 
         */
        void cleanEmiters();

        /**
         * @brief 
         * 
         */
        void cleanAffectors();

        /**
         * @brief 
         * 
         */
        void setEmiter(OBDParticleEmiter*);
        
        /**
         * @brief 
         * 
         */
        void addAffector(OBDParticleAffector*);
    private:
        TNode* particleSystemNode;

        std::vector<OBDParticleEmiter*> emiters;
        std::vector<OBDParticleAffector*> affectors;
};

#endif