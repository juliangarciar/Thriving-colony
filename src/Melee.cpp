#include "Melee.h"

//The teamData and vectorData are passed to the father, because as the ranged class,
//also share the same components
Melee::Melee(Enumeration::UnitType::SubClass unitData, Vector3<float> *vectorData, Enumeration::Team teamData) : Unit(vectorData, teamData)
{
    switch (unitData)
    {
    //Basic stats of each unit are here
    //Basic melee soldier
    case Enumeration::UnitType::SubClass::StandardM:
        this->moveSpeed = 420;
        this->attackDamage = 15;
        this->attackRange = 150;
        this->attackSpeed = 1;
        this->viewRange = 600;
        this->hpMax = 80;
        this->hp = 80;
        break;
    //Advanced melee soldier (mounted)
    case Enumeration::UnitType::SubClass::AdvancedM:
        this->moveSpeed = 530;
        this->attackDamage = 21;
        this->attackRange = 180;
        this->attackSpeed = 1;
        this->viewRange = 600;
        this->hpMax = 140;
        this->hp = 140;
        break;
    //Idol (to be defined)
    case Enumeration::UnitType::SubClass::Idol:
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
    this->modelLayer = new SceneNode();
    this->model = new Model(modelLayer, std::rand()); //ToDo: cambiar
    this->model->getModel()->setPosition(vectorData->getVectorF());
    this->model->getModel()->setMaterialFlag(video::EMF_LIGHTING, false);
    Window::Instance()->getSceneManager()->getMeshManipulator()->setVertexColors(model->getModel()->getMesh(), video::SColor(125, 125, 0, 125));
    this->type = unitData;
}
//It's empty because there are nothing to delete
//maybe this will change in a futur
Melee::~Melee() {

}