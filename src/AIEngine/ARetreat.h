#ifndef ARETREAT_H
#define ARETREAT_H

#include "Action.h"

/**
 * @class ARetreat
 * @brief Crea un objeto tipo ARetreat
 */
class ARetreat : public Action {
    
    public:
        /**
         * @brief Constructor de ARetreat
         */
        ARetreat();
        /**
         * @brief Destructor de ARetreat
         */
        virtual ~ARetreat();

        Enumeration::BehaviourState Update();

    private:
};

#endif