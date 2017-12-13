#include "Melee.h"

//The teamData and vectorData are passed to the father, because as the ranged class,
//also share the same components
Melee::Melee(Enumeration::MeleeType unitData, Vector3<float> *vectorData, bool teamData) : Unit(vectorData, teamData)
{
    switch (unitData)
    {
    //Basic stats of each unit are here
    //Basic melee soldier
    case Enumeration::StandardM:
        this->moveSpeed = 420;
        this->attackDamage = 15;
        this->attackRange = 150;
        this->attackSpeed = 1;
        this->viewRange = 600;
        this->hpMax = 80;
        this->hp = 80;
        break;
    //Advanced melee soldier (mounted)
    case Enumeration::AdvancedM:
        this->moveSpeed = 530;
        this->attackDamage = 21;
        this->attackRange = 180;
        this->attackSpeed = 1;
        this->viewRange = 600;
        this->hpMax = 140;
        this->hp = 140;
        break;
    //Idol (to be defined)
    case Enumeration::Idol:
        this->moveSpeed = 250;
        this->attackDamage = 27;
        this->attackRange = 850;
        this->attackSpeed = 1;
        this->viewRange = 600;
        this->hpMax = 180;
        this->hp = 180;
        break;
    }
    //Graphic engine, this should be in the switch (when models done)
    this->hitbox = new Box3D<float>();
    this->model = new Model();
}
//It's empty because there are nothing to delete
//maybe this will change in a futur
Melee::~Melee() {

}