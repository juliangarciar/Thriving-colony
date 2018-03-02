#ifndef ABUILD_H
#define ABUILD_H

#include "Action.h"

/**
 * @class ABuild
 * @brief Crea un objeto tipo ABuild
 */
class ABuild : Action {
    
    public:
        /**
         * @brief Constructor de ABuild
         */
        ABuild(Enumeration::BuildingType);
        /**
         * @brief Destructor de ABuild
         */
        virtual ~ABuild();

        Enumeration::BehaviourState Update();
        void Execute();

    private:
        Enumeration::BuildingType type;
};

#endif