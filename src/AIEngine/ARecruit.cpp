#include "ARecruit.h"
#include "../IA.h"

ARecruit::ARecruit() : Action() {

}

ARecruit::~ARecruit() {

}

Enumeration::BehaviourState ARecruit::Update(std::string type) {
    if (type == "DefenseStandardM") {
        type = "StandardM";
    }
    //A saber como se llaman las tropas equisde
    if ((type == "StandardM" || type == "StandardR") && IA::Instance() -> getTree() -> getBarracks() == 0) {
        // Si puede pagarlo sigue
        if (!IA::Instance() -> getBuildingManager() -> checkCanPay(type))
            return Enumeration::BehaviourState::Failure; 

        BuildingData data = IA::Instance()->getBuildingManager()->getBuildingData("Barrack");
        Box2D dummy(Vector2<f32>(0,0), Vector2<f32>(data.cellsX * cSize, data.cellsY * cSize));
        Vector2<f32> v = IA::Instance() -> determinatePositionBuilding(dummy);
        IA::Instance() -> getBuildingManager() -> createBuilding(v, "Barrack", false);
        IA::Instance() -> getTree() -> addBarrack();
    } else if ((type == "AdvancedM" || type == "Idol") && IA::Instance() -> getTree() -> getBarns() == 0) {
        // Si puede pagarlo sigue
        if (!IA::Instance() -> getBuildingManager() -> checkCanPay(type))
            return Enumeration::BehaviourState::Failure; 

        BuildingData data = IA::Instance()->getBuildingManager()->getBuildingData("Barn");
        Box2D dummy(Vector2<f32>(0,0), Vector2<f32>(data.cellsX * cSize, data.cellsY * cSize));
        Vector2<f32> v = IA::Instance() -> determinatePositionBuilding(dummy);
        IA::Instance() -> getBuildingManager() -> createBuilding(v, "Barn", false);
        IA::Instance() -> getTree() -> addBarn();
    } else if ((type == "Desintegrator" || type == "Cannon") && IA::Instance() -> getTree() -> getBarns() == 0) {
        // Si puede pagarlo sigue
        if (!IA::Instance() -> getBuildingManager() -> checkCanPay(type))
            return Enumeration::BehaviourState::Failure; 

        BuildingData data = IA::Instance()->getBuildingManager()->getBuildingData("Workshop");
        Box2D dummy(Vector2<f32>(0,0), Vector2<f32>(data.cellsX * cSize, data.cellsY * cSize));
        Vector2<f32> v = IA::Instance() -> determinatePositionBuilding(dummy);
        IA::Instance() -> getBuildingManager() -> createBuilding(v, "Workshop", false);
        IA::Instance() -> getTree() -> addWorkshop();
    }




    IA::Instance() -> getUnitManager() -> createTroop(type);
    return Enumeration::BehaviourState::Success;
}

Enumeration::BehaviourState ARecruit::Update() {
    return Enumeration::BehaviourState::Failure;
}