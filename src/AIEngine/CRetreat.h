#ifndef CRETREAT_H
#define CRETREAT_H

#include "Condition.h"

/**
 * @class CRetreat
 * @brief Crea un objeto tipo CRetreat
 */
class CRetreat : public Condition {
    
    public:
        /**
         * @brief Constructor de CRetreat
         */
        CRetreat(Action*);
        /**
         * @brief Destructor de CRetreat
         */
        virtual ~CRetreat();

        Enumeration::BehaviourState Update();

    private:
};

#endif