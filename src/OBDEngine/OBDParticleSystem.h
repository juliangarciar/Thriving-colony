#ifndef OBDPARTICLESYSTEM_H
#define OBDPARTICLESYSTEM_H

#include "OBDSceneNode.h"
#include "OBDParticleEmiter.h"

class OBDParticleSystem : public OBDEntity {
    
    public:
        /**
         * @brief 
         * 
         */
        OBDParticleSystem();

        /**
         * @brief 
         * 
         * @param
         */
        OBDParticleSystem(OBDSceneNode*, i32, glm::vec3, glm::vec3, glm::vec3);

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

         /**
         * @brief Get the First Node object
         * 
         * @return TNode* 
         */
        TNode *getFirstNode();

    private:
        TNode* particleSystemNode;
        TNode* rotationNode;
        TNode* translationNode;
        TNode* scaleNode;

        i32 ID;

        OBDParticleEmiter emiter;
};

#endif