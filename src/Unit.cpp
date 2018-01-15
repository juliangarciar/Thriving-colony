#include "Unit.h"
#include "Game.h"
#include "Human.h"
#include "IA.h"

//ToDo: cambiar llamada a entity
Unit::Unit(int id, SceneNode *layer, Vector3<float> vectorData, Enumeration::Team teamData, Enumeration::UnitType typeData, Enumeration::RaceType raceData) : Entity(layer, id, 100) {
    //Actions of the units
    this->moving = false;
    this->attacking = false;
    this->retracted = true;
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
    // Target-scanning timers
    this -> lookForTargetTimer = 5;
    this -> lookForTargetCountdown = lookForTargetTimer;
    this -> attackCountdown = 0;
    switch (unitType)
    {
    //Basic stats of each unit are here
    //Basic melee soldier
    /**
     * 
     * MELEE A PIE
     * 
     * 
     */
    case Enumeration::UnitType::StandardM:
        if(unitRace == Enumeration::RaceType::Drorania){
            this->moveSpeed = 420;
            this->attackDamage = 15;
            this->attackRange = 140;
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
            this->attackRange = 140;
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
            this->attackRange = 140;
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
            this->attackRange = 140;
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
            this->attackRange = 140;
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
            this->attackRange = 140;
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
    /**
     * 
     * RANGO A PIE
     * 
     * 
     */
    case Enumeration::UnitType::StandardR:
        if(unitRace == Enumeration::RaceType::Drorania){
            this->moveSpeed = 350;
            this->attackDamage = 13;
            this->attackRange = 600;
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
            this->attackRange = 600;
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
            this->attackRange = 700;
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
            this->attackRange = 700;
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
            this->attackRange = 900;
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
            this->attackRange = 900;
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
            this->attackRange = 120;
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
            this->attackRange = 120;
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
    delete vectorPos;
    delete vectorDes;
    delete vectorMov;
}

void Unit::attack() {
    if (target != NULL) {
        setAttacking(true);
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
        if (std::abs(vectorDes -> x - position -> x) < 5.0 && std::abs(vectorDes -> z - position->z) < 5.0) {
            moving = false;
        } else {
            Vector3<float> newPos = *vectorPos + *vectorMov;
            newPos.y = Game::Instance()->getGameState()->getMap()->getY(newPos.x, newPos.z);
            this->setTroopPosition(newPos);
        }
    }
}

void Unit::updateTroop() {
    moveTroop();
    float dt = Game::Instance() -> getWindow() -> getDeltaTime();
    
    if (retracted == false) {
        // NO tengo objetivo, busco uno
        if (target == NULL) {
            // Look for a new target every 5 seconds (subject to change)
            if (lookForTargetCountdown <= 0) {
                Game::Instance() -> getGameState() -> getBattleManager() -> askForTarget(this);
                lookForTargetCountdown = lookForTargetTimer;
            } else {
                lookForTargetCountdown -= dt;
            }
            // tengo objetivo
        } else {
            // If the target is alive, this should probably be changed later on, but it is needed for now
            if (target -> getHP() > 0) {
                //The target is withing reach
                if (inRangeOfAttack()) {
                    if (attackCountdown <= 0) {
                        attack();
                        attackCountdown = attackSpeed;
                    } else {
                        attackCountdown -= dt;
                    }
                } else {
                    // Start moving towards them
                    //chaseTarget();
                    setTroopDestination(Vector3<float>(target -> getPosition() -> x, target -> getPosition() -> y, target -> getPosition() -> z));
                }
            } else {
                target = NULL;
                setAttacking(false);
            }
        }
    }
}

void Unit::setTroopPosition(Vector3<float> vectorData) {
    this -> vectorPos -> set(vectorData);
    this -> setPosition(vectorData);
}

void Unit::setTroopDestination(Vector3<float> vectorData) {
    setAttacking(false);
    target = NULL;

    vectorDes -> set(vectorData);

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
void Unit::updateTarget(Entity *newTarget) {
    // target can be null, meaning that he cant attack anything
    target = newTarget;
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

bool Unit::inRangeOfAttack() {
    bool inRange = false;
    float xaux = target -> getPosition() -> x - position -> x;
    float yaux = target -> getPosition() -> y - position -> y;
    float dist = sqrtf(pow(xaux, 2) - pow(yaux, 2));
    if (dist <= attackRange) {
        inRange = true;
    }
    return inRange;
}

bool Unit::getRetracted() {
    return retracted;
}

bool Unit::getMoving() {
    return moving;
}

Vector3<float>* Unit::getDestination() {
    return vectorDes;
}

void Unit::setRetracted(bool data) {
    retracted = data;
}