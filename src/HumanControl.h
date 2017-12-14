#ifndef HUMANCONTROL_H
#define HUMANCONTROL_H
#include <iostream>
#include "Unit.h"
#include <irrlicht.h>
#include <list>
class HumanControl{
    private:
        //std::list< *Unit > totalUnits;
        Unit *selectedUnits;
        int size;
    public:
        HumanControl();
        ~HumanControl();

        //void update();
        //GETTERS
        bool ifUnitSelected();
        //SETTERS
        void selectUnit(Unit *UnitData);
        void unselectUnit();
};

#endif