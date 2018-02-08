#ifndef BATTLE_MANAGER_H
#define BATTLE_MANAGER_H

#include <vector>
#include "GraphicEngine/Vector2.h"
#include "Enumeration.h"
//#include "Entity.h"
#include "Unit.h"
#include "Building.h"
#include <Types.h>

/**
 * @class BattleManager
 * @brief Crea un objeto tipo BattleManager
 */
class BattleManager {
    
    public:
        /**
         * @brief Constructor de BattleManager
         */
        BattleManager();
        /**
         * @brief Destructor de BattleManager
         */
        virtual ~BattleManager();
        /**
         * @brief Solicita un objetivo para la entidad, analizando sus caracteristicas de ataque
         * @param Entity sera la entidad que solicita un objetivo
         */
        void askForTarget(Entity*);

    private:

};

#endif