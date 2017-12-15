#ifndef MELEE_H
#define MELEE_H

#include "Unit.h"
#include "GraphicEngine/Window.h"
#include "GraphicEngine/SceneNode.h"

class Melee : public Unit {
    
    public:
        //Enum: Standard, Advanced, Idol
        //teamData sepecifies the unit team and vectorData the position
        Melee(Enumeration::UnitType::SubClass unitData, Vector3<float> *vectorData, bool teamData);
        virtual ~Melee();

    private:
      
};

#endif