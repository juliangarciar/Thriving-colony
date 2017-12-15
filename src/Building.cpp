#include "Building.h"

Building::Building(Enumeration::BuildingType buildingData, Vector3<float> *vectorData, bool teamData) : Entity()
{
    switch(buildingData){
        case Enumeration::BuildingType::Barn:
            this->hpMax = 1100;
            this->hp = 1100;
        break;
        case Enumeration::BuildingType::Barrack:
            this->hpMax = 720;
            this->hp = 720;
        break;
        case Enumeration::BuildingType::Hospital:
            this->hpMax = 750;
            this->hp = 750;
            break;
        case Enumeration::BuildingType::House:
            this->hpMax = 150;
            this->hp = 150;
        break;
        case Enumeration::BuildingType::MainBuilding:
            this->hpMax = 3000;
            this->hp = 3000;
        break;
        case Enumeration::BuildingType::Market:
            this->hpMax = 600;
            this->hp = 600;
        break;
        case Enumeration::BuildingType::Quarry:
            this->hpMax = 1000;
            this->hp = 1000;
        break;
        case Enumeration::BuildingType::Siderurgy:
            this->hpMax = 1000;
            this->hp = 1000;
        break;
        case Enumeration::BuildingType::School:
            this->hpMax = 550;
            this->hp = 550;
        break;
        case Enumeration::BuildingType::Tower:
            this->hpMax = 500;
            this->hp = 500;
        break;
        case Enumeration::BuildingType::Wall:
            this->hpMax = 200;
            this->hp = 200;
        break;
        case Enumeration::BuildingType::Workshop:
            this->hpMax = 800;
            this->hp = 800;
        break;
    }
    //Graphic engine, this should be in the switch (when models done)
    this->modelLayer = new SceneNode();
    this->model = new Model(modelLayer);
    this->model->getModel()->setPosition(vectorData->getVectorF());
    this->model->getModel()->setMaterialFlag(video::EMF_LIGHTING, false);
    Window::Instance()->getSceneManager()->getMeshManipulator()->setVertexColors(model->getModel()->getMesh(), video::SColor(125, 125, 0, 125));    
    this->type = buildingData;
    this->position = vectorData;
}

Building::~Building() {
    
}
