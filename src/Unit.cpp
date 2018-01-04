#include "Unit.h"
#include "Game.h"
#include "Human.h"
#include "IA.h"
Unit::Unit(int id, SceneNode *layer, Vector3<float> vectorData, Enumeration::Team teamData, Enumeration::UnitType typeData, Enumeration::RaceType raceData) : Entity(layer, id) {
    //Actions of the units
    this->moving = false;
    this->attacking = false;
    //Default target
    this->target = 0;
    //Position defined by the constructor parameter
    this->vectorPos = new Vector3<float>();
    this->vectorDes = new Vector3<float>();
    this->vectorMov = new Vector3<float>();
    //Team defined by the constructor parameter
    this->team = teamData;
    //Defining model position
    this->model->getModel()->setPosition(vectorData.getVectorF());
    //This should be put in the switch
    int metalCost = 0;
    int crystalCost = 0;
    int happiness = -10;
    //Race type and unit type
    this->unitRace = raceData;
    this->unitType = typeData;
    switch (unitType)
    {
    //Basic stats of each unit are here
    //Basic melee soldier
    case Enumeration::UnitType::StandardM:
        if(unitRace == Enumeration::RaceType::Drorania){
            this->moveSpeed = 420;
            this->attackDamage = 15;
            this->attackRange = 150;
            this->attackSpeed = 1;
            this->viewRange = 600;
            this->hpMax = 80;
            this->hp = 80;
            attackEvent = "UnitAttackDroraniaMeleeS";
            moveEvent = "UnitMovementDroraniaMeleeS";
            selectEvent = "UnitSelectDroraniaMeleeS";
            metalCost = Enumeration::UnitCost::MeleeFootmenMetalCost;
            crystalCost = Enumeration::UnitCost::MeleeFootmenCrystalCost;
        }
        else if(unitRace == Enumeration::RaceType::Kaonov){
            this->moveSpeed = 420;
            this->attackDamage = 15;
            this->attackRange = 150;
            this->attackSpeed = 1;
            this->viewRange = 600;
            this->hpMax = 80;
            this->hp = 80;
            attackEvent = "UnitAttackKaonovMeleeS";
            moveEvent = "UnitMovementKaonovMeleeS";
            selectEvent = "UnitSelectKaonovMeleeS";
            metalCost = Enumeration::UnitCost::MeleeFootmenMetalCost;
            crystalCost = Enumeration::UnitCost::MeleeFootmenCrystalCost;
        }
    break;
    //Advanced melee soldier (mounted)
    case Enumeration::UnitType::AdvancedM:
        if(unitRace == Enumeration::RaceType::Drorania){
            this->moveSpeed = 530;
            this->attackDamage = 21;
            this->attackRange = 180;
            this->attackSpeed = 1;
            this->viewRange = 600;
            this->hpMax = 140;
            this->hp = 140;
            attackEvent = "UnitAttackDroraniaMeleeA";
            moveEvent = "UnitMovementDroraniaMeleeA";
            selectEvent = "UnitSelectDroraniaMeleeA";
            metalCost = Enumeration::UnitCost::MountedMeleeMetalCost;
            crystalCost = Enumeration::UnitCost::MountedMeleeCrystalCost;
        }
        //This should be changed
        else if(unitRace == Enumeration::RaceType::Kaonov){
            this->moveSpeed = 530;
            this->attackDamage = 21;
            this->attackRange = 180;
            this->attackSpeed = 1;
            this->viewRange = 600;
            this->hpMax = 140;
            this->hp = 140;
            attackEvent = "UnitAttackKaonovMeleeA";
            moveEvent = "UnitMovementKaonovMeleeA";
            selectEvent = "UnitSelectKaonovMeleeA";
            metalCost = Enumeration::UnitCost::MountedMeleeMetalCost;
            crystalCost = Enumeration::UnitCost::MountedMeleeCrystalCost;
        }
    break;
    //Idol (to be defined)
    case Enumeration::UnitType::Idol:
        if(unitRace == Enumeration::RaceType::Drorania){
            this->moveSpeed = 250;
            this->attackDamage = 27;
            this->attackRange = 850;
            this->attackSpeed = 1;
            this->viewRange = 600;
            this->hpMax = 180;
            this->hp = 180;
            //TO CHANGE
            attackEvent = "UnitAttackDroraniaMeleeA";
            moveEvent = "UnitMovementDroraniaMeleeA";
            selectEvent = "UnitSelectDroraniaMeleeA";
            metalCost = Enumeration::UnitCost::CreatureMetalCost;
            crystalCost = Enumeration::UnitCost::CreatureCrystalCost;
        }
        else if(unitRace == Enumeration::RaceType::Kaonov){
            this->moveSpeed = 250;
            this->attackDamage = 27;
            this->attackRange = 850;
            this->attackSpeed = 1;
            this->viewRange = 600;
            this->hpMax = 180;
            this->hp = 180;
            //TO CHANGE
            attackEvent = "UnitAttackKaonovMeleeA";
            moveEvent = "UnitMovementKaonovMeleeA";
            selectEvent = "UnitSelectKaonovMeleeA";
            metalCost = Enumeration::UnitCost::CreatureMetalCost;
            crystalCost = Enumeration::UnitCost::CreatureCrystalCost;
        }
    break;
    //Standard ranged unit
    case Enumeration::UnitType::StandardR:
        if(unitRace == Enumeration::RaceType::Drorania){
            this->moveSpeed = 350;
            this->attackDamage = 13;
            this->attackRange = 500;
            this->attackSpeed = 1;
            this->viewRange = 600;
            this->hpMax = 60;
            this->hp = 60;
            attackEvent = "UnitAttackDroraniaRangedS";
            moveEvent = "UnitMovementDroraniaRangedS";
            selectEvent = "UnitSelectDroraniaRangedS";
            metalCost = Enumeration::UnitCost::RangedFootmenMetalCost;
            crystalCost = Enumeration::UnitCost::RangedFootmenCrystalCost;
        }
        else if(unitRace == Enumeration::RaceType::Kaonov){
            this->moveSpeed = 350;
            this->attackDamage = 13;
            this->attackRange = 500;
            this->attackSpeed = 1;
            this->viewRange = 600;
            this->hpMax = 60;
            this->hp = 60;
            attackEvent = "UnitAttackKaonovRangedS";
            moveEvent = "UnitMovementKaonovRangedS";
            selectEvent = "UnitSelectKaonovRangedS";
            metalCost = Enumeration::UnitCost::RangedFootmenMetalCost;
            crystalCost = Enumeration::UnitCost::RangedFootmenCrystalCost;
        }   
    break;
    //Advanced ranged soldier (mounted)
    case Enumeration::UnitType::AdvancedR:
        if(unitRace == Enumeration::RaceType::Drorania){
            this->moveSpeed = 530;
            this->attackDamage = 18;
            this->attackRange = 550;
            this->attackSpeed = 1;
            this->viewRange = 600;
            this->hpMax = 110;
            this->hp = 110;
            attackEvent = "UnitAttackDroraniaRangedA";
            moveEvent = "UnitMovementDroraniaRangedA";
            selectEvent = "UnitSelectDroraniaRangedA";
            metalCost = Enumeration::UnitCost::MountedRangedMetalCost;
            crystalCost = Enumeration::UnitCost::MountedRangedCrystalCost;
        }
        else if(unitRace == Enumeration::RaceType::Kaonov){
            this->moveSpeed = 530;
            this->attackDamage = 18;
            this->attackRange = 550;
            this->attackSpeed = 1;
            this->viewRange = 600;
            this->hpMax = 110;
            this->hp = 110;
            attackEvent = "UnitAttackKaonovRangedA";
            moveEvent = "UnitMovementKaonovRangedA";
            selectEvent = "UnitSelectKaonovRangedA";
            metalCost = Enumeration::UnitCost::MountedRangedMetalCost;
            crystalCost = Enumeration::UnitCost::MountedRangedCrystalCost;
        }
        break;
        //Rock launcher
        case Enumeration::UnitType::Launcher:
        if(unitRace == Enumeration::RaceType::Drorania){
            this->moveSpeed = 250;
            this->attackDamage = 27;
            this->attackRange = 850;
            this->attackSpeed = 1;
            this->viewRange = 600;
            this->hpMax = 180;
            this->hp = 180;
            //CHANGE
            attackEvent = "UnitAttackDroraniaRangedS";
            moveEvent = "UnitMovementDroraniaRangedS";
            selectEvent = "UnitSelectDroraniaRangedS";
            metalCost = Enumeration::UnitCost::CatapultMetalCost;
            crystalCost = Enumeration::UnitCost::CatapultCrystalCost;
        }
        else if(unitRace == Enumeration::RaceType::Kaonov){
            this->moveSpeed = 250;
            this->attackDamage = 27;
            this->attackRange = 850;
            this->attackSpeed = 1;
            this->viewRange = 600;
            this->hpMax = 180;
            this->hp = 180;
            //CHANGE
            attackEvent = "UnitAttackKaonovRangedS";
            moveEvent = "UnitMovementKaonovRangedS";
            selectEvent = "UnitSelectKaonovRangedS";
            metalCost = Enumeration::UnitCost::CatapultMetalCost;
            crystalCost = Enumeration::UnitCost::CatapultCrystalCost;
        }
        break;
        //Wall desintegrator
        case Enumeration::UnitType::Desintegrator:
        if(unitRace == Enumeration::RaceType::Drorania){
            this->moveSpeed = 250;
            this->attackDamage = 41;
            this->attackRange = 180;
            this->attackSpeed = 1;
            this->viewRange = 600;
            this->hpMax = 220;
            this->hp = 220;
            //CHANGE
            attackEvent = "UnitAttackDroraniaRangedA";
            moveEvent = "UnitMovementDroraniaRangedA";
            selectEvent = "UnitSelectDroraniaRangedA";
            metalCost = Enumeration::UnitCost::RamMetalCost;
            crystalCost = Enumeration::UnitCost::RamCrystalCost;
        }
        else if(unitRace == Enumeration::RaceType::Kaonov){
            this->moveSpeed = 250;
            this->attackDamage = 41;
            this->attackRange = 180;
            this->attackSpeed = 1;
            this->viewRange = 600;
            this->hpMax = 220;
            this->hp = 220;
            //CHANGE
            attackEvent = "UnitAttackKaonovRangedA";
            moveEvent = "UnitMovementKaonovRangedA";
            selectEvent = "UnitSelectKaonovRangedA";
            metalCost = Enumeration::UnitCost::RamMetalCost;
            crystalCost = Enumeration::UnitCost::RamCrystalCost;
        }
        break;
    }
    //Graphic engine, this should be in the switch (when models done)
    //this->modelLayer = new SceneNode();
    Window::Instance()->getSceneManager()->getMeshManipulator()->setVertexColors(model->getModel()->getMesh(), video::SColor(125, 125, 0, 125));

    if (teamData == Enumeration::Team::Human)
    {
        Human::getInstance()->increaseHappiness(happiness);
        Human::getInstance()->increaseMeleeAmount();
        Human::getInstance()->spendResources(metalCost, crystalCost);
    }
    else
    {
        IA::getInstance()->increaseHappiness(happiness);
        IA::getInstance()->increaseMeleeAmount();
        IA::getInstance()->spendResources(metalCost, crystalCost);
    }
}

Unit::~Unit() {
    delete target;
    delete vectorPos;
    delete vectorDes;
    delete vectorMov;
}

void Unit::attack() {
    if (target != 0) {
        target -> takeDamage(attackDamage);
    }
}

Entity* Unit::getTarget() {
    return target;
}

void Unit::setMoving(bool movingPnt) {
    moving = movingPnt;
}

void Unit::setAttacking(bool attackingPnt) {
    attacking = attackingPnt;
}
void Unit::moveTroop() {
    if (moving) {
        if (std::abs(vectorDes->x - position->x) < 5.0 && std::abs(vectorDes->z - position->z) < 5.0) {
            moving = false;
        } else {
            this->setTroopPosition(*vectorPos + *vectorMov);
        }
    }
}

void Unit::updateTroop() {
    moveTroop();
}

void Unit::setTroopPosition(Vector3<float> vectorData) {
    this->vectorPos->set(vectorData);
    this->setPosition(vectorData);
}

void Unit::setTroopDestination(Vector3<float> vectorData) {
    vectorDes->set(vectorData);

    Vector3<float> desp = *vectorDes - *vectorPos;

    float distance = std::abs(std::sqrt(std::pow(desp.x, 2) + std::pow(desp.z, 2)));

    vectorMov->x = (desp.x / distance) * moveSpeed * Game::Instance()->getWindow()->getDeltaTime();
    vectorMov->z = (desp.z / distance) * moveSpeed * Game::Instance()->getWindow()->getDeltaTime();

    moving = true;
}

Model* Unit::getModel() {
    return this->model;
}

/*
void Unit::assignBattle(Battle* _battle) {
    battleInvolved = _battle;
}

void Unit::updateTarget() {
    if (battleInvolved != NULL) {
        //ToDo: definir como va a ser lo del equipo porque cada uno dice una cosa y ayer se iba a decidir y no se decidio
        //      por ahora esta que siempre es humano 
        target = battleInvolved -> getClosestTarget(*position, Enumeration::Team::Human);
    }
}*/
string Unit::getAttackEvent(){
    return attackEvent;
}
string Unit::getMoveEvent(){
    return moveEvent;
}
string Unit::getSelectEvent(){
    return selectEvent;
}

void Unit::taxPlayer(Enumeration::Team teamData) {
    //ToDo: si se necesita
}