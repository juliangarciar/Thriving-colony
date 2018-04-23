#ifndef CRECRUIT_H
#define CRECRUIT_H

#include "Condition.h"

/**
 * @class CRecruit
 * @brief Crea un objeto tipo CRecruit
 */
class CRecruit : public Condition {
    
    public:
        /**
         * @brief Constructor de CRecruit
         */
        CRecruit(Action*, Enumeration::UnitType, Enumeration::UnitCost, Enumeration::UnitCost);
        /**
         * @brief Destructor de CRecruit
         */
        virtual ~CRecruit();

        Enumeration::BehaviourState Update();
        void actionToDo();

    private:
        Enumeration::UnitType type;
        Enumeration::UnitCost metal;
        Enumeration::UnitCost crystal;
};

#endif