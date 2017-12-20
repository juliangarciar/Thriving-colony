#include "GameState.h"
#include "Game.h"
#include "Human.h"
#include "IA.h"

GameState::GameState() : State() {
    camera = new CameraController();
    hud = new Hud();
    nodeRootIA = new RootNode();
}

GameState::~GameState() {
    delete nodeRootIA;
    delete camera;
    delete hud;
    delete map;
}

void GameState::Init(){
    map = new Terrain("media/mapa3-256x256.bmp"); //ToDo: mover a map
    map->setTexture(new Texture("media/map-texture.jpg"), new Texture("media/map-detail-texture.jpg")); //ToDo: mover a map

    /*for (int i=0; i < 100; i++){
        Model *m = new Model(std::rand());
        m->setPosition(Vector3<float>(200,1800,200));
        models.push_back(m);
    }*/
}

void GameState::Input(){
    hud->getHUDEvents();

    camera->Move(Game::Instance()->getIO(), Game::Instance()->getCursor());
    camera->RotateAndInclinate(Game::Instance()->getIO(), Game::Instance()->getCursor());
    camera->Zoom(Game::Instance()->getIO());

    Vector3<float> v = map->getPointCollision(Game::Instance()->getCursor());
    if (Game::Instance()->getIO()->leftMousePressed()){
        Human::getInstance() -> getBuildingManager()->testRaycastCollisions();
        int id = Human::getInstance() -> getBuildingManager() -> getCollisionID();
        if (id != -1){
            std::map<int,Building*> *b = Human::getInstance() -> getBuildingManager() -> getBuildings();
            std::map<int,Building*>::iterator it;
            it = b->find(id);
            if (it->second != NULL){
                int t = (int)it->second->getType();
                hud->showPopup(t);
            }
        }
	}
}

void GameState::Update(){
    camera->Update(map, Game::Instance()->getWindow()->getDeltaTime());

    Vector3<float> cam = camera->getCamera()->getCameraPosition();
    Vector3<float> tar = camera->getCamera()->getTargetPosition();

    //buildingManager->drawCube(map);
    Human::getInstance() -> getBuildingManager() -> drawBuilding(map, Enumeration::BuildingType::House,  Enumeration::Team::Human);
    if(!unitDone){
        Vector3<float> *vectorData = new Vector3<float>(200, 200, 200);
        Enumeration::UnitType unitData;
        unitData.unitClass = Enumeration::UnitType::Class::Ranged;
        unitData.unitSubClass = Enumeration::UnitType::SubClass::StandardR;
        Human::getInstance()->getUnitManager()->createTroop(vectorData, unitData);
        this->unitDone = true;
    }
    
    nodeRootIA -> question();

   /* for (int i=0; i < models.size(); i++){
        models.at(i)->setPosition(Vector3<float>(models.at(i)->getPosition().x+1, models.at(i)->getPosition().y, models.at(i)->getPosition().z+1)); 
        //std::cout << " i " << i << " data " << models.at(i)->getPosition() << std::endl;
    }*/
}

void GameState::Render(){

}

void GameState::CleanUp(){

}

Terrain* GameState::getMap() {
    return map;
}