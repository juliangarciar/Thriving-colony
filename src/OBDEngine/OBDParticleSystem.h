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

        OBDParticleEmiter* emiter;
        std::vector<OBDParticleAffector*> affectors;
};

#endif