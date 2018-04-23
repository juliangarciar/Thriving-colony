#ifndef ABUILD_H
#define ABUILD_H

#include "Action.h"

/**
 * @class ABuild.
 * @brief Create a ABuild type object. Public heritage from Action class.
 */
class ABuild : public Action {
    
    public:
         /**
         * @brief ABuild constructor.
         */
        ABuild();

        /**
         * @brief ABuild destructor.
         */
        virtual ~ABuild();

        /**
         * @brief Do nothing. Need to be implemented because of the heritage.
         * 
         * @return Enumeration::BehaviourState::Failure.
         */
        Enumeration::BehaviourState Update();

        /**
         * @brief Do nothing. Need to be implemented because of the heritage.
         * 
         * @return Enumeration::BehaviourState::Failure.
         */
        Enumeration::BehaviourState Update(Enumeration::UnitType);

        /**
         * @brief Build the type of building passed by parameter.
         * 
         * @param The Enumeration::BuildingType is the type of building that is going to be built.
         * @return Enumeration::BehaviourState 
         */
        Enumeration::BehaviourState Update(Enumeration::BuildingType);

    private:
};

#endif