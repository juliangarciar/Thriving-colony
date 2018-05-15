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
        OBDParticleSystem(OBDSceneNode*, glm::vec3);

        /**
         * @brief 
         * 
         */
        ~OBDParticleSystem();

        /**
         * @brief 
         * 
         */
        void clearAffectors();

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
       
        void createPointEmitter(glm::vec3 direction = glm::vec3(0.0f, 0.03f, 0.0f), i32 particlesPerSecond = 5, OBDColor StartColor = OBDColor(255, 0, 0, 0), i32 lifeTime = 2000, i32 maxAngleDegrees = 0, glm::vec2 startSize = glm::vec2(5.0f, 5.0f));

    private:
        TNode* particleSystemNode;

        OBDParticleEmiter* emiter;
        std::vector<OBDParticleAffector*> affectors;
        glm::vec3 position;
};

#endif