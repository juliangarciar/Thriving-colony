#include "ABuild.h"
#include "../IA.h"

ABuild::ABuild(): Action() {

}

ABuild::~ABuild() {

}

Enumeration::BehaviourState ABuild::Update() {
    return Enumeration::BehaviourState::Failure;
}

Enumeration::BehaviourState ABuild::Update(std::string type) {
    Vector2<f32> v(0,0);
    if (type == "DefenseBarrack")
            type = "Barrack";
    if (type == "LastChoiceHouse")
            type = "House";
    BuildingData data = IA::Instance()->getBuildingManager()->getBuildingData(type);
    Box2D dummy(Vector2<f32>(0,0), Vector2<f32>(data.cellsX * cSize, data.cellsY * cSize));
    v = IA::Instance() -> determinatePositionBuilding(dummy);
    // Increase build range
    //Vector2<f32> pos = IA::Instance() -> hallPosition;
    f32 xComp = v.x - IA::Instance() -> hallPosition.x;
    f32 yComp = v.y - IA::Instance() -> hallPosition.y;
    // Si la distancia es menor que el rango - 100 (por si acaso), intenta aumentarlo, si no, sigue
    if (xComp*xComp - yComp*yComp >= (IA::Instance()-> buildableRange - 100)) {
        if (!IA::Instance() -> increaseBuildableRange()) 
            return Enumeration::BehaviourState::Failure;
    }
    // Si puede pagarlo sigue
    IA::Instance() -> getBuildingManager() -> createBuilding(v, type, false);
    // Solo llega aqui si ha podido contruir el edificio, confirma los cambios
    if (type == "Barn"){
            IA::Instance() -> getTree() -> setRequireBarn(false);
            IA::Instance() -> getTree() -> addBarn();
	} else if (type == "Barrack"){
            IA::Instance() -> getTree() -> setRequireBarrack(false);
            IA::Instance() -> getTree() -> addBarrack();
	} else if (type == "DefenseBarrack"){
            IA::Instance() -> getTree() -> setRequireBarrack(false);
            type = "Barrack";
            IA::Instance() -> getTree() -> addBarrack();
	} else if (type == "House"){
            IA::Instance() -> getTree() -> setRequireCitizens(false);
	} else if (type == "LastChoiceHouse") {
            IA::Instance() -> getTree() -> setRequireCitizens(false);
            type = "House";
	} else if (type == "Quarry") {
            IA::Instance() -> getTree() -> setRequireCrystal(false);
	} else if (type == "Workshop") {
            IA::Instance() -> getTree() -> setRequireBarrack(false);
            IA::Instance() -> getTree() -> addWorkshop();
	}

    return Enumeration::BehaviourState::Success;
}