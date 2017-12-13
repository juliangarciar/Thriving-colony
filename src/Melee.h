#ifndef MELEE_H
#define MELEE_H

#include "Unit.h"
#include "Enumeration.h"
#include <iostream>
#include "GraphicEngine/Vector3.h"
#include "GraphicEngine/Model.h"
#include "GraphicEngine/Box3D.h"

class Melee : public Unit {
    
    public:
        //Enum: Standard, Advanced, Idol
        //teamData sepecifies the unit team and vectorData the position
        Melee(Enumeration::MeleeType unitData, Vector3<float> *vectorData, bool teamData);
        virtual ~Melee();

    private:

};

#endif