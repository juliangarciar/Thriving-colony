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
    Vector2<f32> v = IA::Instance() -> determinatePositionBuilding();
    if (type == "Barn"){
            IA::Instance() -> getTree() -> setRequireBarn(false);
	} else if (type == "Barrack"){
            IA::Instance() -> getTree() -> setRequireBarrack(false);
	} else if (type == "DefenseBarrack"){
            IA::Instance() -> getTree() -> setRequireBarrack(false);
            type = "Barrack";
	} else if (type == "House"){
            IA::Instance() -> getTree() -> setRequireCitizens(false);
	} else if (type == "LastChoiceHouse"){
            IA::Instance() -> getTree() -> setRequireCitizens(false);
            type = "House";
	} else if (type == "Quarry"){
            IA::Instance() -> getTree() -> setRequireCrystal(false);
	} else if (type == "Workshop"){
            IA::Instance() -> getTree() -> setRequireBarrack(false);
	} else if (type == "Tower"){
            std::cout<<"torre"<<std::endl;
    }
    IA::Instance() -> getBuildingManager() -> createBuilding(v, type, false);
    return Enumeration::BehaviourState::Success;
}