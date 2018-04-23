#ifndef ACTION_H
#define ACTION_H

#include "Behaviour.h"

/**
 * @class Action.
 * @brief Create a Action type object. Public heritage from Behaviour class.
 */
class Action : public Behaviour {
    
    public:
       /**
         * @brief Action constructor.
         */
        Action();

        /**
         * @brief Action destructor.
         */
        virtual ~Action();

        /**
         * @brief Virtual method that will be implemented at classes that will inherit from Action class.
         * 
         * @return Enumeration::BehaviourState::Success when the action is made and Enumeration::BehaviourState::Failure in other case.
         */
        Enumeration::BehaviourState virtual Update() = 0;

        /**
         * @brief Virtual method that will be implemented at classes that will inherit from Action class.
         * 
         * @param Enumeration::UnitType.
         * @return Enumeration::BehaviourState::Success when the action is made and Enumeration::BehaviourState::Failure in other case.
         */
        Enumeration::BehaviourState virtual Update(Enumeration::UnitType) = 0;

        /**
         * @brief Virtual method that will be implemented at classes that will inherit from Action class.
         * 
         * @param Enumeration::BuildingType.
         * @return Enumeration::BehaviourState::Success when the action is made and Enumeration::BehaviourState::Failure in other case.
         */
        Enumeration::BehaviourState virtual Update(Enumeration::BuildingType) = 0;

    protected:
};

#endif