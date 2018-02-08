#include "Unit.h"
#include "Game.h"
#include "Human.h"
#include "IA.h"

Unit::Unit(SceneNode *layer, i32 id, const wchar_t *path, Enumeration::Team team, Enumeration::BreedType breed, Enumeration::UnitType t, Vector3<f32> p) : Entity(layer, id, path, team, breed) {
    // Race type and unit type
    unitType = t;
    // Defining model position
    model -> setPosition(p);

    // Actions of the units
    finished = false;
    moving = false;
    attacking = false;

    // Default target
    target = NULL;

    //Default state
    state = Enumeration::UnitState::Recruiting;

    //Iniciar
    Init();

    //Tax the player
    //preTaxPlayer();

    // Position defined by the constructor parameter
    vectorPos = new Vector3<f32>();
    vectorDes = new Vector3<f32>();
    vectorMov = new Vector3<f32>();

    // Timers
    recruitingTimer = recruitingTime;
    lookForTargetTimer = 0.5;
    lookForTargetCountdown = lookForTargetTimer;
    attackCountdown = 0;

    // Preparado para algo
    readyToEnter = false;

    // Pathfinding
    pathManager = new PathManager(this);

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
                recruitingTime = 5;
                happiness = -10;
                citizens = -10;
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
                recruitingTime = 5;
                happiness = -10;
                citizens = -10;
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
                recruitingTime = 10;
                happiness = -10;
                citizens = -10;
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
                recruitingTime = 10;
                happiness = -10;
                citizens = -10;
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
                recruitingTime = 5;
                happiness = -10;
                citizens = -10;
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
                recruitingTime = 5;
                happiness = -10;
                citizens = -10;
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
                recruitingTime = 10;
                happiness = -10;
                citizens = -10;
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
                recruitingTime = 10;
                happiness = -10;
                citizens = -10;
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
                recruitingTime = 20;
                happiness = -10;
                citizens = -10;
                //ToDo: CHANGE
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
                recruitingTime = 20;
                happiness = -10;
                citizens = -10;
                //ToDo: CHANGE
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
                recruitingTime = 15;
                happiness = -10;
                citizens = -10;
                //ToDo: CHANGE
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
                recruitingTime = 15;
                happiness = -10;
                citizens = -10;
                //ToDo: CHANGE
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
                recruitingTime = 20;
                happiness = -10;
                citizens = -10;
                //ToDo: CHANGE
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
                recruitingTime = 20;
                happiness = -10;
                citizens = -10;
                //ToDo: CHANGE
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
/*
void Unit::moveTroop() {
    if (moving) {
        // close to destination, stop
        if (std::abs(vectorDes -> x - position -> x) < 5.0 && std::abs(vectorDes -> z - position -> z) < 5.0) {
            moving = false;
            if (state == Enumeration::UnitState::Retract) {
                readyToEnter = true;
                if (team == Enumeration::Team::Human) {
                    Human::Instance() -> getUnitManager() -> enterMainBuilding(unitType);
                } else {
                    IA::Instance() -> getUnitManager() -> enterMainBuilding(unitType);
                }
                return;
            }
            switchState(Enumeration::Idle);
        } else {
            // far from destination, move
            Vector3<float> newPos = *vectorPos + *vectorMov;
            newPos.y = Game::Instance() -> getGameState() -> getTerrain() -> getY(newPos.x, newPos.z);
            setTroopPosition(newPos);
        }
    }
}*/

void Unit::update() {
    returnToOriginalColor(); //ToDo: ¿?
    attackCountdown -= Game::Instance() -> getWindow() -> getDeltaTime();
    //State machine, color changes according to state
    switch (state) {
        case Enumeration::UnitState::Recruiting:
            recruitingState();
        break;
        case Enumeration::UnitState::InHome:
            inHomeState();
        break;
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

void Unit::preTaxPlayer() {
    if (team == Enumeration::Team::Human) {
        Human::Instance() -> spendResources(metalCost, crystalCost);
        Human::Instance() -> increaseHappiness(happiness);
        Human::Instance() -> increaseCitizens(citizens);
    } else {
        IA::Instance() -> spendResources(metalCost, crystalCost);
        IA::Instance() -> increaseHappiness(happiness);
        IA::Instance() -> increaseCitizens(citizens);
    }
}

void Unit::posTaxPlayer(){
    if (team == Enumeration::Team::Human) {
        Human::Instance() -> increaseArmySize();
    } else {
        IA::Instance() -> increaseArmySize();
    }
}

void Unit::switchState(Enumeration::UnitState newState) {
    lookForTargetCountdown = lookForTargetTimer;
    state = newState;
}

void Unit::recruitingState(){
    if (recruitingTimer > 0){
        recruitingTimer -= Game::Instance() -> getWindow() -> getDeltaTime();
    } else {
        recruitedCallback(this);
        switchState(Enumeration::UnitState::InHome);
    }
}

void Unit::inHomeState() {
    //ToDo: hay que hacer algo mientras esté en base?
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
    attackCountdown -= Game::Instance() -> getWindow() -> getDeltaTime();
    // Scan for targets
    if (refreshTarget()) { // i got one
        switchState(Enumeration::UnitState::Chase);
    } else {
        switchState(Enumeration::UnitState::AttackMove);
        moveTroop();  
    }
}

void Unit::attackState() {
    attackCountdown -= Game::Instance() -> getWindow() -> getDeltaTime();
    if(inRangeOfAttack()) {
        attack();
    } else {
        switchState(Enumeration::UnitState::Chase);
    }
}

/// Chasing the target
void Unit::chaseState() {
    //If I have a target, then chase it
    if (target != NULL) {
        Vector3<f32> tpos = Vector3<f32>(0,0,0);
        tpos.x = target -> getPosition() -> x;
        tpos.y = target -> getPosition() -> y;
        tpos.z = target -> getPosition() -> z;
        this  -> setTroopDestination(tpos);
        chaseTarget();    
    }
}

void Unit::retractState() {
    moveTroop();
    if (readyToEnter){
        retractedCallback(this);
        getModel() -> setActive(false);
        switchState(Enumeration::UnitState::InHome);
    }
}

void Unit::moveTroop() {
    if (moving) {
        // close to destination, stop
        if (steps == 0) {
            if(pathFollow.empty()){
                moving = false;
                if (state == Enumeration::UnitState::Retract) {
                    if (team == Enumeration::Team::Human) {
                        Human::Instance() -> getUnitManager() -> enterMainBuilding(unitType);
                    } else {
                        IA::Instance() -> getUnitManager() -> enterMainBuilding(unitType);
                    }
                    return;
                }
                switchState(Enumeration::Idle);
            }
            else{
                Vector2<f32> dummy = this->pathFollow.front();
                Vector3<f32> newDest(dummy.x, Game::Instance() -> getGameState() -> getTerrain() -> getY(dummy.x, dummy.y), dummy.y);
                pathFollow.pop_front();
                setTroopDestination(newDest);
            }
        }
        else if(std::floor(steps) == 0){
            Vector3<f32> move = *vectorMov;
            //move.x *= 1 + Game::Instance() -> getWindow() -> getDeltaTime() * steps;
            //move.z *= 1 + Game::Instance() -> getWindow() -> getDeltaTime() * steps;
            Vector3<f32> newPos = *vectorPos + move;
            newPos.y = Game::Instance() -> getGameState() -> getTerrain() -> getY(newPos.x, newPos.z);
            setTroopPosition(newPos);
            steps = 0;
        } 
        else {
            // far from destination, move
            Vector3<f32> move = *vectorMov;
            //move.x *= 1 + Game::Instance() -> getWindow() -> getDeltaTime();
            //move.z *= 1 + Game::Instance() -> getWindow() -> getDeltaTime();
            Vector3<f32> newPos = *vectorPos + move;
            newPos.y = Game::Instance() -> getGameState() -> getTerrain() -> getY(newPos.x, newPos.z);
            setTroopPosition(newPos);
            steps--;
        }
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
                        IA::Instance() -> getUnitManager() -> deleteUnit(target -> getID());
                    } else {
                        IA::Instance() -> getBuildingManager() -> deleteBuilding(target -> getID());
                    }
                } else {
                    if (target -> getEntityType() == Enumeration::EntityType::Unit) {
                        Human::Instance() -> getUnitManager() -> deleteUnit(target -> getID());
                    } else {
                        Human::Instance() -> getBuildingManager() -> deleteBuilding(target -> getID());
                    }
                }
                target = NULL;
                this -> switchState(Enumeration::UnitState::AttackMove);
            }
        }
    }
}

void Unit::chaseTarget() {
    if (moving) {
        // If i can attack, then do so
        if (inRangeOfAttack()) {
            moving = false;
            switchState(Enumeration::UnitState::Attack);
        } else { //If i am too far away to attack, then move closer.
            Vector3<f32> newPos = *vectorPos + *vectorMov;
            newPos.y = Game::Instance() -> getGameState() -> getTerrain() -> getY(newPos.x, newPos.z);
            setTroopPosition(newPos);
        }
    }
}

bool Unit::inRangeOfAttack() {
    bool inRange = false;
    if (target != NULL) {
        f32 xaux = target -> getPosition() -> x - position -> x;
        f32 yaux = target -> getPosition() -> y - position -> y;
        f32 dist = sqrtf(pow(xaux, 2) - pow(yaux, 2));
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

void Unit::triggerRecruitedCallback(){
    finished = true;
    recruitedCallback(this);
}

void Unit::triggerRetractedCallback(){
    finished = true;
    retractedCallback(this);
}

/////SETTERS/////
void Unit::setMoving(bool movingPnt) {
    moving = movingPnt;
}

void Unit::setAttacking(bool attackingPnt) {
    attacking = attackingPnt;
}

void Unit::setTroopPosition(Vector3<f32> vectorData) {
    vectorPos -> set(vectorData);
    setPosition(vectorData);
}
// To do -> adjust units movement
void Unit::setTroopDestination(Vector3<f32> vectorData) {
    if (state == Enumeration::UnitState::Move) {
        target = NULL;
    }

    vectorDes -> set(vectorData);

    Vector3<f32> desp = *vectorDes - *vectorPos;

    f32 distance = std::sqrt(std::pow(desp.x, 2) + std::pow(desp.z, 2));

    //vectorMov -> x = (desp.x / distance) * moveSpeed * Game::Instance() -> getWindow() -> getDeltaTime();
    //vectorMov -> z = (desp.z / distance) * moveSpeed * Game::Instance() -> getWindow() -> getDeltaTime();
    vectorMov -> x = (desp.x / distance) * (moveSpeed / 100);
    vectorMov -> z = (desp.z / distance) * (moveSpeed / 100);
    f32 movDistance = std::sqrt(std::pow(vectorMov -> x, 2) + std::pow(vectorMov -> z, 2));
    steps = (distance / movDistance);
    std::cout << "Distance: " << distance << "\n";
    std::cout << "Mov distance " << movDistance << "\n"; 
    std::cout << "Steps: " << steps << "\n";
    moving = true;
}

void Unit::setPath(std::list< Vector2<f32> > path){
    this->pathFollow = path;
}

void Unit::setPathToTarget(Vector3<f32> vectorData){
    this->pathManager->createPathTo(vectorData.toVector2());
    if(!pathFollow.empty()){
        Vector2<f32> dummy = this->pathFollow.front();
        Vector3<f32> newDest;
        newDest.x = dummy.x;
        newDest.y = Game::Instance() -> getGameState() -> getTerrain() -> getY(dummy.x, dummy.y);
        newDest.z = dummy.y;
        this->setTroopDestination(newDest);
        this->pathFollow.pop_front();
    }
}

void Unit::setRecruitedCallback(std::function<void(Unit*)> f){
    recruitedCallback = f;
}

void Unit::setRetractedCallback(std::function<void(Unit*)> f){
    retractedCallback = f;
}

/////GETTERS/////
string Unit::getAttackEvent() {
    return attackEvent;
}

string Unit::getMoveEvent() {
    return moveEvent;
}

string Unit::getSelectEvent() {
    return selectEvent;
}

Vector3<f32>* Unit::getDestination() {
    return vectorDes;
}

std::list< Vector2<f32> > Unit::getPath(){
    return pathFollow;
}