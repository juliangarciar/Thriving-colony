#ifndef AREDIRECT_H
#define AREDIRECT_H

#include "Action.h"

/**
 * @class AAttack.
 * @brief Create a AAttack type object. Public heritage from Action class.
 */
class ARedirect : public Action {
    
    public:
        /**
         * @brief AAttack constructor.
         */
        ARedirect();

        /**
         * @brief AAttack destructor.
         */
        virtual ~ARedirect();

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
        Enumeration::BehaviourState Update(std::string);

    private:
};

#endif