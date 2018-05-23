#ifndef OBDPARTICLESYSTEM_H
#define OBDPARTICLESYSTEM_H

#include "OBDSceneNode.h"
#include "OBDParticleEmiter.h"
#include "OBDParticleAffector.h"

class OBDParticleSystem : public OBDEntity {
    
    public:
        /**
         * @brief OBDParticleSystem constructor.
         * 
         * @param OBDSceneNode will be layer where the OBDParticleSystem is going to be created.
         * @param glm::vec3 will be the position where the OBDParticleSystem is going to be created.
         */
        OBDParticleSystem(OBDSceneNode*, glm::vec3);

        /**
         * @brief OBDParticleSystem destructor.
         * 
         */
        ~OBDParticleSystem();

        /**
         * @brief Delete all the affectors in the OBDParticleSystem.
         * 
         */
        void clearAffectors();

        /**
         * @brief Set the emiter that is going to use the OBDParticleSystem.
         * 
         * @param OBDParticleEmiter will be the new emiter of the OBDParticleSystem.
         */
        void setEmiter(OBDParticleEmiter*);
        
        /**
         * @brief Add an affector to the OBDParticleSystem.
         * 
         * @param OBDParticleAffector will be the new affector of the OBDParticleSystem.
         */
        void addAffector(OBDParticleAffector*);
       
        /**
         * @brief Create a emitter of point type.
         * 
         * @param direction will be the direction of the particles.
         * @param particlesPerSecond will be the number of particles per second of the emiter.
         * @param StartColor will be the start color of the particles.
         * @param lifeTime will be the life time of the particles.
         * @param maxAngleDegrees will be the maximum angles with which the emiter is going to emit the particles.
         * @param startSize will be the start size of the particles.
         */
        void createPointEmitter(glm::vec3 direction = glm::vec3(0.0f, 0.03f, 0.0f), i32 particlesPerSecond = 5, OBDColor StartColor = OBDColor(255, 0, 0, 0), i32 lifeTime = 2000, i32 maxAngleDegrees = 0, glm::vec2 startSize = glm::vec2(5.0f, 5.0f));

    private:
        //Pointer to the node of the particle system.
        TNode* particleSystemNode;

        //Emiter that is going to use the OBDParticleSystem.
        OBDParticleEmiter* emiter;

        //Affectors that are going to affect to the emiter of the OBDParticleSystem.
        std::vector<OBDParticleAffector*> affectors;

        //Position of the OBDParticleSystem.
        glm::vec3 position;
};

#endif