#ifndef OBDPARTICLEEMITER_H
#define OBDPARTICLEEMITER_H

#include "OBDSceneNode.h"

#include "Graphics/TBillboard.h"

class OBDParticleEmiter : public OBDEntity {
    
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
        OBDParticleEmiter(OBDSceneNode*, i32, glm::vec3);

        /**
         * @brief 
         * 
         */
        ~OBDParticleEmiter();

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
};

#endif