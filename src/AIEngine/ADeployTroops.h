#ifndef ADEPLOYTROOPS_H
#define ADEPLOYTROOPS_H

#include "Action.h"

/**
 * @class ADeployTroops
 * @brief Crea un objeto tipo ADeployTroops
 */
class ADeployTroops : Action {
    
    public:
        /**
         * @brief Constructor de ADeployTroops
         */
        ADeployTroops();
        /**
         * @brief Destructor de ADeployTroops
         */
        virtual ~ADeployTroops();

        Enumeration::BehaviourState Update();
        void Execute();

    private:
};

#endif