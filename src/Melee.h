#ifndef MELEE_H
#define MELEE_H

#include "Unit.h"
#include "GraphicEngine/Window.h"
#include "GraphicEngine/SceneNode.h"
#include <string>
using namespace std;
class Melee : public Unit {
    
    public:
        //Enum: Standard, Advanced, Idol
        //teamData sepecifies the unit team and vectorData the position
        Melee(int id, SceneNode *layer, Enumeration::UnitType::SubClass unitData, Vector3<float> vectorData, Enumeration::Team teamData);
        virtual ~Melee();

    string getAttackEvent();
    string getMoveEvent();
    string getSelectEvent();
  private:
    string attackEvent;
    string moveEvent;
    string selectEvent;
      
};

#endif