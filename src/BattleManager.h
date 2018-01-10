#ifndef BATTLE_MANAGER_H
#define BATTLE_MANAGER_H

#include <vector>
#include "GraphicEngine/Vector2.h"
#include "Enumeration.h"
//#include "Entity.h"
#include "Unit.h"
#include "Building.h"

class BattleManager {
    
    public:
        BattleManager();
        virtual ~BattleManager();

        

        void askForTarget(Entity*);

    private:

};

#endif