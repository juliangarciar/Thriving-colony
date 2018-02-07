#include "Unit.h"
#include "Game.h"
#include "Human.h"
#include "IA.h"

Unit::Unit(SceneNode *layer, int id, const wchar_t *path, Enumeration::Team team, Enumeration::BreedType breed, Enumeration::UnitType t, Vector3<float> p) : Entity(layer, id, path, team, breed) {
    // Esto lo pongo a pelo e igual para todas
    // ToDo: ¿Seguro? ¿no deberian tener felicidades diferentes?
    happiness = -10;
    // Race type and unit type
    unitType = t;
    // Defining model position
    model -> setPosition(p);

    // Actions of the units
    moving = false;
    attacking = false;
    retracted = true;
    // Default target
    target = NULL;
    // Position defined by the constructor parameter
    vectorPos = new Vector3<float>();
    vectorDes = new Vector3<float>();
    vectorMov = new Vector3<float>();
    // Target-scanning timers
    lookForTargetTimer = 0.5;
    lookForTargetCountdown = lookForTargetTimer;
    attackCountdown = 0;
    // Preparado para algo
    readyToEnter = false;
    pathManager = new PathManager(this);
    Init();

    //Graphic engine, this should be in the switch (when models done)
    setColor(video::SColor(125, 125, 0, 125)); //ToDo: cambiar por material
}

Unit::~Unit() {
    delete vectorPos;
    delete vectorDes;
    delete vectorMov;
    delete pathManager;
}

void Unit::Init() {
    // Basic stats of each unit are here
    switch (unitType) {
        // Basic melee soldier
        case Enumeration::UnitType::StandardM:
            if (breed == Enumeration::BreedType::Drorania) {
                moveSpeed = 420;
                attackDamage = 15;
                attackRange = 100;
                attackSpeed = 1;
                viewRadius = 450;
                maxHP = 80;
                currentHP = 80;
                attackEvent = "event:/UnitAttack/Drorania_melee_S";
                moveEvent = "event:/UnitMovement/Drorania_melee_S";
                selectEvent = "event:/UnitSelect/Drorania_melee_S";
                metalCost = Enumeration::UnitCost::MeleeFootmenMetalCost;
                crystalCost = Enumeration::UnitCost::MeleeFootmenCrystalCost;
            } else if (breed == Enumeration::BreedType::Kaonov) {
                moveSpeed = 420;
                attackDamage = 15;
                attackRange = 100;
                attackSpeed = 1;
                viewRadius = 450;
                maxHP = 80;
                currentHP = 80;
                attackEvent = "event:/UnitAttack/Kaonov_melee_S";
                moveEvent = "event:/UnitMovement/Kaonov_melee_S";
                selectEvent = "event:/UnitSelect/Kaonov_melee_S";
                metalCost = Enumeration::UnitCost::MeleeFootmenMetalCost;
                crystalCost = Enumeration::UnitCost::MeleeFootmenCrystalCost;
            }
        break;
        //Advanced melee soldier (mounted)
        case Enumeration::UnitType::AdvancedM:
            if (breed == Enumeration::BreedType::Drorania) {
                moveSpeed = 530;
                attackDamage = 21;
                attackRange = 140;
                attackSpeed = 1;
                viewRadius = 450;
                maxHP = 140;
                currentHP = 140;
                attackEvent = "event:/UnitAttack/Drorania_melee_A";
                moveEvent = "event:/UnitMovement/Drorania_melee_A";
                selectEvent = "event:/UnitSelect/Drorania_melee_A";
                metalCost = Enumeration::UnitCost::MountedMeleeMetalCost;
                crystalCost = Enumeration::UnitCost::MountedMeleeCrystalCost;
            } else if (breed == Enumeration::BreedType::Kaonov) {
                //This should be changed
                moveSpeed = 530;
                attackDamage = 21;
                attackRange = 140;
                attackSpeed = 1;
                viewRadius = 450;
                maxHP = 140;
                currentHP = 140;
                attackEvent = "event:/UnitAttack/Kaonov_melee_A";
                moveEvent = "event:/UnitMovement/Kaonov_melee_A";
                selectEvent = "event:/UnitSelect/Kaonov_melee_A";
                metalCost = Enumeration::UnitCost::MountedMeleeMetalCost;
                crystalCost = Enumeration::UnitCost::MountedMeleeCrystalCost;
            }
        break;
        //Standard ranged unit
        case Enumeration::UnitType::StandardR:
            if (breed == Enumeration::BreedType::Drorania) {
                moveSpeed = 350;
                attackDamage = 13;
                attackRange = 350;
                attackSpeed = 1;
                viewRadius = 450;
                maxHP = 60;
                currentHP = 60;
                attackEvent = "event:/UnitAttack/Drorania_ranged_S";
                moveEvent = "event:/UnitMovement/Drorania_ranged_S";
                selectEvent = "event:/UnitSelect/Drorania_ranged_S";
                metalCost = Enumeration::UnitCost::RangedFootmenMetalCost;
                crystalCost = Enumeration::UnitCost::RangedFootmenCrystalCost;
            } else if (breed == Enumeration::BreedType::Kaonov) {
                moveSpeed = 350;
                attackDamage = 13;
                attackRange = 350;
                attackSpeed = 1;
                viewRadius = 450;
                maxHP = 60;
                currentHP = 60;
                attackEvent = "event:/UnitAttack/Kaonov_ranged_S";
                moveEvent = "event:/UnitMovement/Kaonov_ranged_S";
                selectEvent = "event:/UnitSelect/Kaonov_ranged_S";
                metalCost = Enumeration::UnitCost::RangedFootmenMetalCost;
                crystalCost = Enumeration::UnitCost::RangedFootmenCrystalCost;
            }   
        break;
        //Advanced ranged soldier (mounted)
        case Enumeration::UnitType::AdvancedR:
            if (breed == Enumeration::BreedType::Drorania) {
                moveSpeed = 530;
                attackDamage = 18;
                attackRange = 700;
                attackSpeed = 1;
                viewRadius = 450;
                maxHP = 110;
                currentHP = 110;
                attackEvent = "event:/UnitAttack/Drorania_ranged_A";
                moveEvent = "event:/UnitMovement/Drorania_ranged_A";
                selectEvent = "event:/UnitSelect/Drorania_ranged_A";
                metalCost = Enumeration::UnitCost::MountedRangedMetalCost;
                crystalCost = Enumeration::UnitCost::MountedRangedCrystalCost;
            } else if (breed == Enumeration::BreedType::Kaonov) {
                moveSpeed = 530;
                attackDamage = 18;
                attackRange = 700;
                attackSpeed = 1;
                viewRadius = 450;
                maxHP = 110;
                currentHP = 110;
                attackEvent = "event:/UnitAttack/Kaonov_ranged_A";
                moveEvent = "event:/UnitMovement/Kaonov_ranged_A";
                selectEvent = "event:/UnitSelect/Kaonov_ranged_A";
                metalCost = Enumeration::UnitCost::MountedRangedMetalCost;
                crystalCost = Enumeration::UnitCost::MountedRangedCrystalCost;
            }
        break;
        //Idol (to be defined)
        case Enumeration::UnitType::Idol:
            if (breed == Enumeration::BreedType::Drorania) {
                moveSpeed = 250;
                attackDamage = 27;
                attackRange = 140;
                attackSpeed = 1;
                viewRadius = 450;
                maxHP = 180;
                currentHP = 180;
                //ToDo CHANGE
                attackEvent = "event:/UnitAttack/Drorania_melee_A";
                moveEvent = "event:/UnitMovement/Drorania_melee_A";
                selectEvent = "event:/UnitSelect/Drorania_melee_A";
                metalCost = Enumeration::UnitCost::CreatureMetalCost;
                crystalCost = Enumeration::UnitCost::CreatureCrystalCost;
            } else if (breed == Enumeration::BreedType::Kaonov) {
                moveSpeed = 250;
                attackDamage = 27;
                attackRange = 140;
                attackSpeed = 1;
                viewRadius = 450;
                maxHP = 180;
                currentHP = 180;
                //ToDo CHANGE
                attackEvent = "event:/UnitAttack/Kaonov_melee_A";
                moveEvent = "event:/UnitMovement/Kaonov_melee_A";
                selectEvent = "event:/UnitSelect/Kaonov_melee_A";
                metalCost = Enumeration::UnitCost::CreatureMetalCost;
                crystalCost = Enumeration::UnitCost::CreatureCrystalCost;
            }
        break;
        //Rock launcher
        case Enumeration::UnitType::Launcher:
            if (breed == Enumeration::BreedType::Drorania) {
                moveSpeed = 250;
                attackDamage = 27;
                attackRange = 900;
                attackSpeed = 1;
                viewRadius = 450;
                maxHP = 180;
                currentHP = 180;
                //CHANGE
                attackEvent = "event:/UnitAttack/Drorania_ranged_S";
                moveEvent = "event:/UnitMovement/Drorania_ranged_S";
                selectEvent = "event:/UnitSelect/Drorania_ranged_S";
                metalCost = Enumeration::UnitCost::CatapultMetalCost;
                crystalCost = Enumeration::UnitCost::CatapultCrystalCost;
            } else if (breed == Enumeration::BreedType::Kaonov) {
                moveSpeed = 250;
                attackDamage = 27;
                attackRange = 900;
                attackSpeed = 1;
                viewRadius = 450;
                maxHP = 180;
                currentHP = 180;
                //CHANGE
                attackEvent = "event:/UnitAttack/Kaonov_ranged_S";
                moveEvent = "event:/UnitMovement/Kaonov_ranged_S";
                selectEvent = "event:/UnitSelect/Kaonov_ranged_S";
                metalCost = Enumeration::UnitCost::CatapultMetalCost;
                crystalCost = Enumeration::UnitCost::CatapultCrystalCost;
            }
        break;
        //Wall desintegrator
        case Enumeration::UnitType::Desintegrator:
            if (breed == Enumeration::BreedType::Drorania) {
                moveSpeed = 250;
                attackDamage = 41;
                attackRange = 120;
                attackSpeed = 1;
                viewRadius = 450;
                maxHP = 220;
                currentHP = 220;
                //CHANGE
                attackEvent = "event:/UnitAttack/Drorania_ranged_A";
                moveEvent = "event:/UnitMovement/Drorania_ranged_A";
                selectEvent = "event:/UnitSelect/Drorania_ranged_A";
                metalCost = Enumeration::UnitCost::RamMetalCost;
                crystalCost = Enumeration::UnitCost::RamCrystalCost;
            } else if (breed == Enumeration::BreedType::Kaonov) {
                moveSpeed = 250;
                attackDamage = 41;
                attackRange = 120;
                attackSpeed = 1;
                viewRadius = 450;
                maxHP = 220;
                currentHP = 220;
                //CHANGE
                attackEvent = "event:/UnitAttack/Kaonov_ranged_A";
                moveEvent = "event:/UnitMovement/Kaonov_ranged_A";
                selectEvent = "event:/UnitSelect/Kaonov_ranged_A";
                metalCost = Enumeration::UnitCost::RamMetalCost;
                crystalCost = Enumeration::UnitCost::RamCrystalCost;
            }
        break;
        default: break;
    }
}

void Unit::moveTroop() {
    if (moving) {
        // close to destination, stop
        if (steps == 0) {
            if(pathFollow.empty()){
                moving = false;
                if (state == Enumeration::UnitState::Retract) {
                    readyToEnter = true;
                    return;
                }
                switchState(Enumeration::Idle);
            }
            else{
                Vector2<float> dummy = this->pathFollow.front();
                Vector3<float> newDest(dummy.x, Game::Instance() -> getGameState() -> getTerrain() -> getY(dummy.x, dummy.y), dummy.y);
                pathFollow.pop_front();
                setTroopDestination(newDest);
            }
        }
        else if(std::floor(steps) == 0){
            Vector3<float> move = *vectorMov;
            move.x *= steps;
            //move.y *= steps;
            move.z *= steps;
            Vector3<float> newPos = *vectorPos + move;
            newPos.y = Game::Instance() -> getGameState() -> getTerrain() -> getY(newPos.x, newPos.z);
            this -> setTroopPosition(newPos);
            steps = 0;
        } 
        else {
            // far from destination, move
            Vector3<float> newPos = *vectorPos + *vectorMov;
            newPos.y = Game::Instance() -> getGameState() -> getTerrain() -> getY(newPos.x, newPos.z);
            setTroopPosition(newPos);
            steps--;
        }
    }
}

void Unit::updateTroop() {
    returnToOriginalColor(); //ToDo: ¿?
    attackCountdown -= Game::Instance() -> getWindow() -> getDeltaTime();
    //State machine, color changes according to state
    switch (state) {
        case Enumeration::UnitState::Idle:
            setColor(video::SColor(255, 0, 255, 255)); //ToDo: cambiar por materiales
            idleState();
            break;
        case Enumeration::UnitState::Move:
            setColor(video::SColor(255, 255, 0, 255)); //ToDo: cambiar por materiales
            moveState();
            break;
        case Enumeration::UnitState::AttackMove:
            setColor(video::SColor(255, 255, 255, 0)); //ToDo: cambiar por materiales
            attackMoveState();
            break;
        case Enumeration::UnitState::Attack:
            setColor(video::SColor(255, 0, 0, 0)); //ToDo: cambiar por materiales
            attackState();
            break;    
        case Enumeration::UnitState::Chase:
            setColor(video::SColor(255, 255, 255, 255)); //ToDo: cambiar por materiales
            chaseState();
            break;
        case Enumeration::UnitState::Retract:
            setColor(video::SColor(255, 127, 127, 127)); //ToDo: cambiar por materiales
            retractState();
            break;
        default: break;
    }
}

void Unit::taxPlayer(Enumeration::Team teamData) {
    if (teamData == Enumeration::Team::Human) {
        Human::getInstance() -> increaseHappiness(happiness);
        Human::getInstance() -> increaseArmySize();
        Human::getInstance() -> spendResources(metalCost, crystalCost);
        Human::getInstance() -> increaseCitizens(citizens);
    } else {
        IA::getInstance() -> increaseHappiness(happiness);
        IA::getInstance() -> increaseArmySize();
        IA::getInstance() -> spendResources(metalCost, crystalCost);
        IA::getInstance() -> increaseCitizens(citizens);
    }
}

bool Unit::inRangeOfAttack() {
    bool inRange = false;
    if (target != NULL) {
        float xaux = target -> getPosition() -> x - position -> x;
        float yaux = target -> getPosition() -> y - position -> y;
        float dist = sqrtf(pow(xaux, 2) - pow(yaux, 2));
        if (dist <= attackRange) {
            inRange = true;
        }
    }
    return inRange;
}

bool Unit::refreshTarget() {
    bool targetUpdated = false;

    // Ask for a new target
    if (lookForTargetCountdown <= 0) {
        Game::Instance() -> getGameState() -> getBattleManager() -> askForTarget(this);
        lookForTargetCountdown = lookForTargetTimer;
    } else {
        lookForTargetCountdown -= Game::Instance() -> getWindow() -> getDeltaTime();
    }
    
    // return wether or not it got updated
    if (target != NULL) {
        targetUpdated = true;
    } else {
        targetUpdated = false;
    }   
    return targetUpdated;
}

void Unit::switchState(Enumeration::UnitState newState) {
    lookForTargetCountdown = lookForTargetTimer;
    state = newState;
}

void Unit::idleState() {
    if (refreshTarget()) { // i got one
        switchState(Enumeration::UnitState::Chase);
    }
}

void Unit::moveState() {
    moveTroop();
}

void Unit::attackMoveState() {
    // Scan for targets
    if (refreshTarget()) { // i got one
        switchState(Enumeration::UnitState::Chase);
    } else {
        switchState(Enumeration::UnitState::AttackMove);
        moveTroop();  
    }
}

void Unit::attackState() {
    if(inRangeOfAttack()) {
        attack();
    } else {
        switchState(Enumeration::UnitState::Chase);
    }
}

void Unit::attack() {
    if (target != NULL) {
        setAttacking(true);
        if (attackCountdown <= 0) {
            target -> takeDamage(attackDamage);
            attackCountdown = attackSpeed;
            if (target -> getHP() <= 0) {
                if (team == Enumeration::Team::Human) {
                    if (target -> getEntityType() == Enumeration::EntityType::Unit) {
                        IA::getInstance() -> getUnitManager() -> deleteUnit(target -> getID());
                    } else {
                        IA::getInstance() -> getBuildingManager() -> deleteBuilding(target -> getID());
                    }
                } else {
                    if (target -> getEntityType() == Enumeration::EntityType::Unit) {
                        Human::getInstance() -> getUnitManager() -> deleteUnit(target -> getID());
                    } else {
                        Human::getInstance() -> getBuildingManager() -> deleteBuilding(target -> getID());
                    }
                }
                target = NULL;
                this -> switchState(Enumeration::UnitState::AttackMove);
            }
        }
    }
}

/// Chasing the target
void Unit::chaseState() {
    //If I have a target, then chase it
    if (target != NULL) {
        Vector3<float> tpos = Vector3<float>(0,0,0);
        tpos.x = target -> getPosition() -> x;
        tpos.y = target -> getPosition() -> y;
        tpos.z = target -> getPosition() -> z;
        this  -> setTroopDestination(tpos);
        chaseTarget();    
    }
}

void Unit::chaseTarget() {
    if (moving) {
        // If i can attack, then do so
        if (inRangeOfAttack()) {
            moving = false;
            switchState(Enumeration::UnitState::Attack);
        } else { //If i am too far away to attack, then move closer.
            Vector3<float> newPos = *vectorPos + *vectorMov;
            newPos.y = Game::Instance() -> getGameState() -> getTerrain() -> getY(newPos.x, newPos.z);
            setTroopPosition(newPos);
        }
    }
}

void Unit::retractState() {
    moveTroop();
}

void Unit::setMoving(bool movingPnt) {
    moving = movingPnt;
}

void Unit::setAttacking(bool attackingPnt) {
    attacking = attackingPnt;
}
void Unit::setRetracted(bool data) {
    retracted = data;
}

void Unit::setTroopPosition(Vector3<float> vectorData) {
    vectorPos -> set(vectorData);
    setPosition(vectorData);
}

void Unit::setTroopDestination(Vector3<float> vectorData) {
    if (state == Enumeration::UnitState::Move) {
        target = NULL;
    }

    vectorDes -> set(vectorData);

    Vector3<float> desp = *vectorDes - *vectorPos;

    float distance = std::sqrt(std::pow(desp.x, 2) + std::pow(desp.z, 2));

    vectorMov -> x = (desp.x / distance) * moveSpeed * Game::Instance() -> getWindow() -> getDeltaTime();
    vectorMov -> z = (desp.z / distance) * moveSpeed * Game::Instance() -> getWindow() -> getDeltaTime();

    float movDistance = std::sqrt(std::pow(vectorMov -> x, 2) + std::pow(vectorMov -> z, 2));
    steps = (distance / movDistance);

    std::cout << "Steps: " << steps << "\n";
    moving = true;
}

void Unit::setPath(std::list< Vector2<float> > path){
    this->pathFollow = path;
}
void Unit::setPathToTarget(Vector3<float> vectorData){
    this->pathManager->createPathTo(vectorData.toVector2());
    if(!pathFollow.empty()){
        Vector2<float> dummy = this->pathFollow.front();
        Vector3<float> newDest;
        newDest.x = dummy.x;
        newDest.y = Game::Instance() -> getGameState() -> getTerrain() -> getY(dummy.x, dummy.y);
        newDest.z = dummy.y;
        this->setTroopDestination(newDest);
        this->pathFollow.pop_front();
    }
}

Entity* Unit::getTarget() {
    return target;
}
Model* Unit::getModel() {
    return model;
}

string Unit::getAttackEvent() {
    return attackEvent;
}
string Unit::getMoveEvent() {
    return moveEvent;
}
string Unit::getSelectEvent() {
    return selectEvent;
}

bool Unit::getReadyToEnter() {
    return readyToEnter;
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
std::list< Vector2<float> > Unit::getPath(){
    return pathFollow;
}