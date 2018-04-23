#ifndef AATTACK_H
#define AATTACK_H

#include "Action.h"

/**
 * @class AAttack.
 * @brief Create a AAttack type object. Public heritage from Action class.
 */
class AAttack : public Action {
    
    public:
        /**
         * @brief AAttack constructor.
         */
        AAttack();

        /**
         * @brief AAttack destructor.
         */
        virtual ~AAttack();

        /**
         * @brief Deploy all AI's troops and send them to the human's city.
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