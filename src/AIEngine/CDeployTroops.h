#ifndef CDEPLOYTROOPS_H
#define CDEPLOYTROOPS_H

#include "Condition.h"

/**
 * @class CDeployTroops
 * @brief Crea un objeto tipo CDeployTroops
 */
class CDeployTroops : public Condition {
    
    public:
        /**
         * @brief Constructor de CDeployTroops
         */
        CDeployTroops(Action*);
        /**
         * @brief Destructor de CDeployTroops
         */
        virtual ~CDeployTroops();

        Enumeration::BehaviourState Update();

    private:
};

#endif