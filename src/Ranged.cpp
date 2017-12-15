#include "Ranged.h"

//The teamData and vectorData are passed to the father, because as the melee class,
//also share the same components
Ranged::Ranged(Enumeration::UnitType::SubClass unitData, Vector3<float> *vectorData, bool teamData) : Unit(vectorData, teamData)
{
    switch(unitData){
        //Basic stats of each unit are here
        //Basic ranged soldier
        case Enumeration::UnitType::SubClass::StandardR:
            this->moveSpeed = 350;
            this->attackDamage = 13;
            this->attackRange = 500;
            this->attackSpeed = 1;
            this->viewRange = 600;
            this->hpMax = 60;
            this->hp = 60;  
        break;
        //Advanced ranged soldier (mounted)
        case Enumeration::UnitType::SubClass::AdvancedR:
            this->moveSpeed = 530;
            this->attackDamage = 18;
            this->attackRange = 550;
            this->attackSpeed = 1;
            this->viewRange = 600;
            this->hpMax = 110;
            this->hp = 110;
        break;
        //Rock launcher
        case Enumeration::UnitType::SubClass::Launcher:
            this->moveSpeed = 250;
            this->attackDamage = 27;
            this->attackRange = 850;
            this->attackSpeed = 1;
            this->viewRange = 600;
            this->hpMax = 180;
            this->hp = 180;
        break;
        //Wall desintegrator
        case Enumeration::UnitType::SubClass::Desintegrator:
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
<<<<<<< HEAD
    //this->hitbox = new Box3D<float>();
    this->modelLayer = new SceneNode();
    this->model = new Model(modelLayer);
    this->model->getModel()->setPosition(vectorData->getVectorF());
    this->model->getModel()->setMaterialFlag(video::EMF_LIGHTING, false);
    Window::Instance()->getSceneManager()->getMeshManipulator()->setVertexColors(model->getModel()->getMesh(), video::SColor(125, 125, 0, 125));
=======
    this->hitbox = new Box3D<float>();
    this->model = new Model(std::rand());
>>>>>>> GraphicEngine
    this->type = unitData;
}
//It's empty because there are nothing to delete
//maybe this will change in a future
Ranged::~Ranged() {
    
}