#ifndef OBDPARTICLESYSTEM_H
#define OBDPARTICLESYSTEM_H

#include "OBDSceneNode.h"

#include "Graphics/TBillboard.h"

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
        OBDParticleSystem(OBDSceneNode*, i32, glm::vec3);

        /**
         * @brief 
         * 
         */
        ~OBDParticleSystem();

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
};

#endif