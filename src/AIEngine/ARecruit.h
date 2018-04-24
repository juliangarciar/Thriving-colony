#ifndef ARECRUIT_H
#define ARECRUIT_H

#include "Action.h"

/**
 * @class ARecruit.
 * @brief Create a ARecruit type object. Public heritage from Action class.
 */
class ARecruit : public Action {
    
    public:
        /**
         * @brief ARecruit constructor.
         */

        ARecruit();

        /**
         * @brief ARecruit destructor.
         */
        virtual ~ARecruit();

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
        Enumeration::BehaviourState Update(std::string);

    private:
};

#endif