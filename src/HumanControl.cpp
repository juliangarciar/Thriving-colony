#include "HumanControl.h"
HumanControl::HumanControl(){
    //Constructor
    selectedUnits = NULL;
    size = 0;
}
HumanControl::~HumanControl(){
    //Destructor
    delete selectedUnits;
    //delete totalUnits;
}

//void HumanControl::update(){
//    for(int i = 0; i < size; i++){
//        totalUnits[i]->updateTroop();
//    }
//}
void HumanControl::selectUnit(Unit *UnitData){
    selectedUnits = UnitData;
}
bool HumanControl::ifUnitSelected(){
    if(this->selectedUnits == NULL)
        return false;
    else    
        return true;
}
void HumanControl::unselectUnit(){
    this->selectedUnits = NULL;
}