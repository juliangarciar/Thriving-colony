#include "Ranged.h"

//The teamData and vectorData are passed to the father, because as the melee class,
//also share the same components
Ranged::Ranged(Enumeration::RangedType unitData, Vector3<float> *vectorData, bool teamData) : Unit(vectorData, teamData)
{
    switch(unitData){
        //Basic stats of each unit are here
        //Basic ranged soldier
        case Enumeration::StandardR:
            this->moveSpeed = 350;
            this->attackDamage = 13;
            this->attackRange = 500;
            this->attackSpeed = 1;
            this->viewRange = 600;
            this->hpMax = 60;
            this->hp = 60;  
        break;
        //Advanced ranged soldier (mounted)
        case Enumeration::AdvancedR:
            this->moveSpeed = 530;
            this->attackDamage = 18;
            this->attackRange = 550;
            this->attackSpeed = 1;
            this->viewRange = 600;
            this->hpMax = 110;
            this->hp = 110;
        break;
        //Rock launcher
        case Enumeration::Launcher:
            this->moveSpeed = 250;
            this->attackDamage = 27;
            this->attackRange = 850;
            this->attackSpeed = 1;
            this->viewRange = 600;
            this->hpMax = 180;
            this->hp = 180;
        break;
        //Wall desintegrator
        case Enumeration::Desintegrator:
            this->moveSpeed = 250;
            this->attackDamage = 41;
            this->attackRange = 180;
            this->attackSpeed = 1;
            this->viewRange = 600;
            this->hpMax = 220;
            this->hp = 220;
        break;
    }
    //Graphic engine, this should be in the switch (when models done)
    this->hitbox = new Box3D<float>();
    this->model = new Model();
}
//It's empty because there are nothing to delete
//maybe this will change in a future
Ranged::~Ranged() {
    
}