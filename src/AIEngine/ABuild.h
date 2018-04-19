#ifndef ABUILD_H
#define ABUILD_H

#include "Action.h"

/**
 * @class ABuild
 * @brief Crea un objeto tipo ABuild
 */
class ABuild : public Action {
    
    public:
        /**
         * @brief Constructor de ABuild
         */
        ABuild();
        /**
         * @brief Destructor de ABuild
         */
        virtual ~ABuild();

        Enumeration::BehaviourState Update();
        Enumeration::BehaviourState Update(Enumeration::UnitType);
        Enumeration::BehaviourState Update(Enumeration::BuildingType);

    private:
};

#endif