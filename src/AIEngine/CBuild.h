#ifndef CBUILD_H
#define CBUILD_H

#include "Condition.h"

/**
 * @class CBuild
 * @brief Crea un objeto tipo CBuild
 */
class CBuild : public Condition {
    
    public:
        /**
         * @brief Constructor de CBuild
         */
        CBuild(Action*, Enumeration::BuildingType, Enumeration::BuildingCost, Enumeration::BuildingCost);
        /**
         * @brief Destructor de CBuild
         */
        virtual ~CBuild();

        Enumeration::BehaviourState Update();
        void actionToDo();

    private:
        Enumeration::BuildingType type;
        Enumeration::BuildingCost metal;
        Enumeration::BuildingCost crystal;
};

#endif