#ifndef ADEPLOYTROOPS_H
#define ADEPLOYTROOPS_H

#include "Action.h"

/**
 * @class ADeployTroops.
 * @brief Create a ADeployTroops type object. Public heritage from Action class.
 */
class ADeployTroops : public Action {
    
    public:
        /**
         * @brief ADeployTroops constructor.
         */
        ADeployTroops();
        
        /**
         * @brief ADeployTroops destructor.
         */
        virtual ~ADeployTroops();

        /**
         * @brief Deploy all AI's troops to defend the city.
         * 
         * @return Enumeration::BehaviourState::Success. 
         */
        Enumeration::BehaviourState Update();
        
        /**
         * @brief Do nothing. Need to be implemented because of the heritage.
         * 
         * @return Enumeration::BehaviourState::Failure.
         */
        Enumeration::BehaviourState Update(Enumeration::UnitType);

        /**
         * @brief Do nothing. Need to be implemented because of the heritage.
         * 
         * @return Enumeration::BehaviourState::Failure.
         */
        Enumeration::BehaviourState Update(Enumeration::BuildingType);

    private:
};

#endif