#include "Unit.h"

#include "Game.h"
#include "Human.h"
#include "IA.h"
#include "Map.h"
#include "Hud.h"
#include "GraphicEngine/Window.h"
#include "Troop.h"
#include <WorldEngine/WorldGeometry.h>

Unit::Unit(SceneNode *l, i32 id, Enumeration::Team team, Enumeration::BreedType breed, Enumeration::UnitType t) : Entity(id, team, breed) {
    // Race type and unit type
    type = t;
    layer = l;

    // Actions of the units
    finished = false;
    moving = false;
    attacking = false;

    // Default target
    target = nullptr;

    //Default state
    state = Enumeration::UnitState::Recruiting;

    entityType = Enumeration::EntityType::Unit;

    //Iniciar
    Init();

    // Timers
    lookForTargetTimer = new Timer (0.5,true);
    // Esto puede ser un timer?
    attackCountdown = 0;

    // Preparado para algo
    readyToEnter = false;

    // Pathfinding
    pathManager = new PathManager(this);

    //Graphic engine, this should be in the switch (when models done)
    setColor(video::SColor(125, 125, 0, 125)); //ToDo: cambiar por material

}

Unit::~Unit() {
    WorldGeometry::Instance()->clearUnitCell(vectorPos.toVector2(), this);
    delete lookForTargetTimer;
    delete pathManager;
    delete troops;
    delete recruitingTimer;
}

void Unit::Init() {
    // Box2D parameters
    Vector2<f32> topLeft;
    Vector2<f32> bottomRight;

    //Texture *tex;
    const wchar_t *path;
    // Basic stats of each unit are here
    f32 recruitingTime = 0;
    switch (type) {
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
                armyLevel = Enumeration::ArmyLevel::Footmen;
                attackEvent = "event:/UnitAttack/Drorania_melee_S";
                moveEvent = "event:/UnitMovement/Drorania_melee_S";
                selectEvent = "event:/UnitSelect/Drorania_melee_S";
                metalCost = Enumeration::UnitCost::MeleeFootmenMetalCost;
                crystalCost = Enumeration::UnitCost::MeleeFootmenCrystalCost;
                path = L"media/unitModels/Drorania/Melee_Soldier_Drorania.obj";
                setModel(layer, path);
                troops = new Troop(layer, path, 4, ID);
                //tex = new Texture("./media/textures/Drorania/Unit/drorania_melee_soldier.jpg");
            } else if (breed == Enumeration::BreedType::Kaonov) {
                moveSpeed = 420;
                attackDamage = 1000;
                attackRange = 100;
                attackSpeed = 1;
                viewRadius = 450;
                maxHP = 80;
                currentHP = 80;
                recruitingTime = 5;
                happiness = -10;
                citizens = -10;
                armyLevel = Enumeration::ArmyLevel::Footmen;
                attackEvent = "event:/UnitAttack/Kaonov_melee_S";
                moveEvent = "event:/UnitMovement/Kaonov_melee_S";
                selectEvent = "event:/UnitSelect/Kaonov_melee_S";
                metalCost = Enumeration::UnitCost::MeleeFootmenMetalCost;
                crystalCost = Enumeration::UnitCost::MeleeFootmenCrystalCost;
                path = L"media/unitModels/Kaonov/kaonov_melee_soldier.obj";
                setModel(layer, path);
                 troops = new Troop(layer, path, 4, ID);
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
                armyLevel = Enumeration::ArmyLevel::Mounted;
                attackEvent = "event:/UnitAttack/Drorania_melee_A";
                moveEvent = "event:/UnitMovement/Drorania_melee_A";
                selectEvent = "event:/UnitSelect/Drorania_melee_A";
                metalCost = Enumeration::UnitCost::MountedMeleeMetalCost;
                crystalCost = Enumeration::UnitCost::MountedMeleeCrystalCost;
                path = L"media/unitModels/Drorania/criatura_drorania.obj";
                //tex = new Texture("./media/textures/Drorania/Unit/drorania_criature.jpg");
                setModel(layer, path);
                //troops = new Troop(layer, path, 4, ID);
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
                armyLevel = Enumeration::ArmyLevel::Mounted;
                attackEvent = "event:/UnitAttack/Kaonov_melee_A";
                moveEvent = "event:/UnitMovement/Kaonov_melee_A";
                selectEvent = "event:/UnitSelect/Kaonov_melee_A";
                metalCost = Enumeration::UnitCost::MountedMeleeMetalCost;
                crystalCost = Enumeration::UnitCost::MountedMeleeCrystalCost;
                path = L"media/unitModels/Kaonov/creature_kaonov.obj";
                setModel(layer, path);
                //troops = new Troop(layer, path, 4, ID);
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
                armyLevel = Enumeration::ArmyLevel::Footmen;
                attackEvent = "event:/UnitAttack/Drorania_ranged_S";
                moveEvent = "event:/UnitMovement/Drorania_ranged_S";
                selectEvent = "event:/UnitSelect/Drorania_ranged_S";
                metalCost = Enumeration::UnitCost::RangedFootmenMetalCost;
                crystalCost = Enumeration::UnitCost::RangedFootmenCrystalCost;
                path = L"media/unitModels/Drorania/rank_soldier_drorania.obj";
                //tex = new Texture("./media/textures/Drorania/Unit/drorania_rank_soldier.jpg");
                setModel(layer, path);
                troops = new Troop(layer, path, 4, ID);
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
                armyLevel = Enumeration::ArmyLevel::Footmen;
                attackEvent = "event:/UnitAttack/Kaonov_ranged_S";
                moveEvent = "event:/UnitMovement/Kaonov_ranged_S";
                selectEvent = "event:/UnitSelect/Kaonov_ranged_S";
                metalCost = Enumeration::UnitCost::RangedFootmenMetalCost;
                crystalCost = Enumeration::UnitCost::RangedFootmenCrystalCost;
                path = L"media/unitModels/Kaonov/kaonov_rank_soldier.obj";
                setModel(layer, path);
                troops = new Troop(layer, path, 4, ID);
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
                armyLevel = Enumeration::ArmyLevel::Mounted;
                attackEvent = "event:/UnitAttack/Drorania_ranged_A";
                moveEvent = "event:/UnitMovement/Drorania_ranged_A";
                selectEvent = "event:/UnitSelect/Drorania_ranged_A";
                metalCost = Enumeration::UnitCost::MountedRangedMetalCost;
                crystalCost = Enumeration::UnitCost::MountedRangedCrystalCost;
                path = L"media/unitModels/Drorania/criatura_drorania.obj";
                //tex = new Texture("./media/textures/Drorania/Unit/drorania_criature.jpg");
                setModel(layer, path);
                troops = new Troop(layer, path, 0, ID);
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
                armyLevel = Enumeration::ArmyLevel::Mounted;
                attackEvent = "event:/UnitAttack/Kaonov_ranged_A";
                moveEvent = "event:/UnitMovement/Kaonov_ranged_A";
                selectEvent = "event:/UnitSelect/Kaonov_ranged_A";
                metalCost = Enumeration::UnitCost::MountedRangedMetalCost;
                crystalCost = Enumeration::UnitCost::MountedRangedCrystalCost;
                path = L"media/unitModels/Kaonov/creature_kaonov.obj";
                setModel(layer, path);
                troops = new Troop(layer, path, 0, ID);
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
                armyLevel = Enumeration::ArmyLevel::Creatures;
                //ToDo: CHANGE
                attackEvent = "event:/UnitAttack/Drorania_melee_A";
                moveEvent = "event:/UnitMovement/Drorania_melee_A";
                selectEvent = "event:/UnitSelect/Drorania_melee_A";
                metalCost = Enumeration::UnitCost::CreatureMetalCost;
                crystalCost = Enumeration::UnitCost::CreatureCrystalCost;
                path = L"media/unitModels/Drorania/Ente_Drorania.obj";
                //tex = new Texture("./media/textures/Drorania/Unit/drorania_entity.jpg");
                setModel(layer, path);
                troops = new Troop(layer, path, 0, ID);
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
                armyLevel = Enumeration::ArmyLevel::Creatures;
                //ToDo: CHANGE
                attackEvent = "event:/UnitAttack/Kaonov_melee_A";
                moveEvent = "event:/UnitMovement/Kaonov_melee_A";
                selectEvent = "event:/UnitSelect/Kaonov_melee_A";
                metalCost = Enumeration::UnitCost::CreatureMetalCost;
                crystalCost = Enumeration::UnitCost::CreatureCrystalCost;
                path = L"media/unitModels/Kaonov/entinity_kaonov.obj";
                setModel(layer, path);
                troops = new Troop(layer, path, 0, ID);
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
                armyLevel = Enumeration::ArmyLevel::Siege;
                //ToDo: CHANGE
                attackEvent = "event:/UnitAttack/Drorania_ranged_S";
                moveEvent = "event:/UnitMovement/Drorania_ranged_S";
                selectEvent = "event:/UnitSelect/Drorania_ranged_S";
                metalCost = Enumeration::UnitCost::CatapultMetalCost;
                crystalCost = Enumeration::UnitCost::CatapultCrystalCost;
                path = L"media/unitModels/Drorania/dorania_cannon.obj";
                setModel(layer, path);
                troops = new Troop(layer, path, 0, ID);
            } 
            else if (breed == Enumeration::BreedType::Kaonov) {
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
                armyLevel = Enumeration::ArmyLevel::Siege;
                //ToDo: CHANGE
                attackEvent = "event:/UnitAttack/Kaonov_ranged_S";
                moveEvent = "event:/UnitMovement/Kaonov_ranged_S";
                selectEvent = "event:/UnitSelect/Kaonov_ranged_S";
                metalCost = Enumeration::UnitCost::CatapultMetalCost;
                crystalCost = Enumeration::UnitCost::CatapultCrystalCost;
                path = L"media/unitModels/Kaonov/kaonov_cannon.obj";
                setModel(layer, path);
                troops = new Troop(layer, path, 0, ID);
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
                armyLevel = Enumeration::ArmyLevel::Siege;
                //ToDo: CHANGE
                attackEvent = "event:/UnitAttack/Drorania_ranged_A";
                moveEvent = "event:/UnitMovement/Drorania_ranged_A";
                selectEvent = "event:/UnitSelect/Drorania_ranged_A";
                metalCost = Enumeration::UnitCost::RamMetalCost;
                crystalCost = Enumeration::UnitCost::RamCrystalCost;
                path = L"media/unitModels/Drorania/drorania_walls_desintegrator.obj";
                setModel(layer, path);
                troops = new Troop(layer, path, 0, ID);
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
                armyLevel = Enumeration::ArmyLevel::Siege;
                //ToDo: CHANGE
                attackEvent = "event:/UnitAttack/Kaonov_ranged_A";
                moveEvent = "event:/UnitMovement/Kaonov_ranged_A";
                selectEvent = "event:/UnitSelect/Kaonov_ranged_A";
                metalCost = Enumeration::UnitCost::RamMetalCost;
                crystalCost = Enumeration::UnitCost::RamCrystalCost;
                path = L"media/unitModels/Kaonov/kaonov_walls_desintegrator.obj";
                setModel(layer, path);
                troops = new Troop(layer, path, 0, ID);
            }
        break;
        default: break;
    }
    recruitingTimer = new Timer(recruitingTime, false);
    //Material *m = new Material(tex);
    //model -> setMaterial(m);
    setModel(layer, path);
    troops = new Troop(layer, path, 4, ID);
    preTaxPlayer();
}

void Unit::update() {
    //returnToOriginalColor(); //ToDo: daba segfault aqui en el arbol very unhappy
    attackCountdown -= Window::Instance() -> getDeltaTime();
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
        Human::Instance() -> increaseArmyLevel(armyLevel);
    } else {
        IA::Instance() -> spendResources(metalCost, crystalCost);
        IA::Instance() -> increaseHappiness(happiness);
        IA::Instance() -> increaseCitizens(citizens);
        IA::Instance() -> increaseArmyLevel(armyLevel);
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
    lookForTargetTimer -> restart();
    state = newState;
}

void Unit::recruitingState(){
    if (recruitingTimer -> tick()){
        recruitedCallback(this);
        switchState(Enumeration::UnitState::InHome);
    } else {
        if (team == Enumeration::Team::Human){
            Hud::Instance() -> modifyTroopFromQueue(ID, recruitingTimer -> getElapsedTime()/recruitingTimer -> getMaxDuration());
        }
    }
}

void Unit::idleState() {
    if (refreshTarget()) { // if got one
        switchState(Enumeration::UnitState::Chase);
    }
}

void Unit::moveState() {
    moveTroop();
}

void Unit::attackMoveState() {
    attackCountdown -= Window::Instance() -> getDeltaTime();
    // Scan for targets
    if (refreshTarget()) { // if got one
        switchState(Enumeration::UnitState::Chase);
    } else {
        switchState(Enumeration::UnitState::AttackMove);
        moveTroop();  
    }
}

void Unit::attackState() {
    attackCountdown -= Window::Instance() -> getDeltaTime();
    if(inRangeOfAttack()) {
        attack();
    } else {
        switchState(Enumeration::UnitState::Chase);
    }
}

/// Chasing the target
void Unit::chaseState() {
    //If I have a target, then chase it
    if (target != nullptr) {
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
        troops -> setActive(false);
        getModel() -> setActive(false);
        switchState(Enumeration::UnitState::InHome);
        // Aqui peta
        triggerRetractedCallback();        
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
                    Human::Instance() -> getUnitManager() -> unSelectTroop();
                    //triggerRetractedCallback();
                    return;
                }
                switchState(Enumeration::Idle);
            }
            else{
                Vector2<f32> dummy = this->pathFollow.front();
                Vector3<f32> newDest(dummy.x, Map::Instance() -> getTerrain() -> getY(dummy.x, dummy.y), dummy.y);
                pathFollow.pop_front();
                setTroopDestination(newDest);
            }
        }
        // Update Cell state 
        else if(std::floor(steps) == 0){
            Vector3<f32> move = vectorMov;
            Vector3<f32> newPos = vectorPos + move;
            newPos.y = Map::Instance() -> getTerrain() -> getY(newPos.x, newPos.z);
            WorldGeometry::Instance()->updateUnitCell(vectorPos.toVector2(), newPos.toVector2(), this);
            WorldGeometry::Instance()->getNeighborUnits(newPos.toVector2());
            setTroopPosition(newPos);
            troops -> moveTroops(move);
            steps = 0;
        } 
        else {
            // far from destination, move
            Vector3<f32> move = vectorMov;
            Vector3<f32> newPos = vectorPos + move;
            newPos.y = Map::Instance() -> getTerrain() -> getY(newPos.x, newPos.z);
            WorldGeometry::Instance()->updateUnitCell(vectorPos.toVector2(), newPos.toVector2(), this);
            WorldGeometry::Instance()->getNeighborUnits(newPos.toVector2());
            setTroopPosition(newPos);
            troops -> moveTroops(move);
            steps--;
        }
    }
}

void Unit::attack() {
    if (target != nullptr && target -> getTeam() != team) {
        setAttacking(true);
        if (attackCountdown <= 0) {
            target -> takeDamage(attackDamage);
            attackCountdown = attackSpeed;
            if (target -> getHP() <= 0) {
                if (target -> getTarget() != nullptr) {
                    target -> getTarget() -> removeHostile(target);
                }
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
                target = nullptr;
                switchState(Enumeration::UnitState::AttackMove);
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
            Vector3<f32> newPos = vectorPos + vectorMov;
            newPos.y = Map::Instance() -> getTerrain() -> getY(newPos.x, newPos.z);
            setTroopPosition(newPos);
        }
    }
}

bool Unit::inRangeOfAttack() {
    bool inRange = false;
    if (target != nullptr) {
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
    if (lookForTargetTimer -> tick()) {
        Game::Instance() -> getGameState() -> getBattleManager() -> askForTarget(this); //ToDo: La hipocresia
    }
    // return wether or not it got updated
    if (target != nullptr) {
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
    retractedCallback(this);
}

/////SETTERS/////
void Unit::setUnitCell(Vector2<f32> vectorPosition){
    WorldGeometry::Instance() -> setUnitCell(vectorPosition, this);
}

void Unit::setMoving(bool movingPnt) {
    moving = movingPnt;
}

void Unit::setAttacking(bool attackingPnt) {
    attacking = attackingPnt;
}

void Unit::setTroopPosition(Vector3<f32> vectorData) {
    vectorPos.set(vectorData);
    setPosition(vectorData);
    troops -> setPosition(vectorData);
}
// To do -> adjust units movement
void Unit::setTroopDestination(Vector3<f32> vectorData) {
    if (state == Enumeration::UnitState::Move) {
        target = nullptr;
    }

    vectorDes.set(vectorData);
    Vector3<f32> desp = vectorDes - vectorPos;
    f32 distance = std::sqrt(std::pow(desp.x, 2) + std::pow(desp.z, 2));
    vectorMov.x = (desp.x / distance) * (moveSpeed / 100);
    vectorMov.z = (desp.z / distance) * (moveSpeed / 100);
    f32 movDistance = std::sqrt(std::pow(vectorMov.x, 2) + std::pow(vectorMov.z, 2));
    steps = (distance / movDistance);
    moving = true;
}

void Unit::setPath(std::list< Vector2<f32> > path){
    this->pathFollow = path;
}

void Unit::setPathToTarget(Vector3<f32> vectorData){
    this->pathManager -> createPathTo(vectorData.toVector2());
    if(!pathFollow.empty()){
        Vector2<f32> dummy = pathFollow.front();
        Vector3<f32> newDest;
        newDest.x = dummy.x;
        newDest.y = Map::Instance() -> getTerrain() -> getY(dummy.x, dummy.y);
        newDest.z = dummy.y;
        setTroopDestination(newDest);
        pathFollow.pop_front();
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

Vector3<f32> Unit::getDestination() {
    return vectorDes;
}

std::list< Vector2<f32> > Unit::getPath(){
    return pathFollow;
}

Enumeration::UnitType Unit::getType(){
    return type;
}

Enumeration::UnitState Unit::getState() {
    return state;
}