#ifndef ARECRUIT_H
#define ARECRUIT_H

#include "Action.h"

/**
 * @class ARecruit
 * @brief Crea un objeto tipo ARecruit
 */
class ARecruit : public Action {
    
    public:
        /**
         * @brief Constructor de ARecruit
         */
        ARecruit();
        /**
         * @brief Destructor de ARecruit
         */
        virtual ~ARecruit();

        Enumeration::BehaviourState Update(Enumeration::UnitType);

    private:
};

#endif