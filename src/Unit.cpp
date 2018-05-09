#include "Unit.h"

#include "Human.h"
#include "IA.h"
#include "Map.h"
#include "Hud.h"
#include "GraphicEngine/Window.h"
#include <WorldEngine/WorldGeometry.h>
#include <functional>
#include <cmath>
#include "UnitFighter.h"

Unit::Unit(SceneNode* _layer, 
    i32 _id, 
    Enumeration::Team _team, 
    UnitData baseData):Entity(
                        _layer,
                        _id,
                        _team,
                        Enumeration::EntityType::Unit,
                        baseData.maxHP,
                        baseData.viewRadius,
                        baseData.attackRange,
                        baseData.attackDamage,
                        baseData.attackSpeed,
                        baseData.metalCost,
                        baseData.crystalCost,
                        baseData.happinessVariation,
                        baseData.citizensVariation,
                        1,
                        1,
                        baseData.flagModel,
                        baseData.flagTexture
                        ),
                        state(Enumeration::UnitState::Recruiting),
                        type(baseData.type),
                        moveSpeed(baseData.moveSpeed),
                        attackSpeed(baseData.attackSpeed),
                        attackDamage(baseData.attackDamage),
                        finished(false),
                        moving(false),
                        attacking(false),
                        armyLevel(baseData.armyLevel),
                        attackCountdown(0),
                        pathManager(nullptr),
                        pathFollow(),
                        vectorDes(0,0),
                        vectorMov(0,0),
                        steps(0),
                        readyToEnter(false),
                        attackEvent(baseData.attackEvent),
                        moveEvent(baseData.moveEvent),
                        selectEvent(baseData.selectEvent),
                        unitFighters()         
{
    lookForTargetTimer = new Timer (0.5, true);
    lookForTargetTimer -> setCallback([&](){
        // Ask for a new target
        //Game::Instance() -> getGameState() -> getBattleManager() -> askForTarget(this);
    });

    recruitingTimer = new Timer(baseData.recruitingTime, false);
    recruitingTimer -> setCallback([&](){
        recruitedCallback(this);
        switchState(Enumeration::UnitState::InHome);
    });
    pathManager = new PathManager(this);

    Texture *t = new Texture(baseData.flagTexture.c_str());


    unitFighters = std::vector< UnitFighter* >(baseData.troops, nullptr);
    for(std::size_t i = 0; i < unitFighters.size(); i++){
        unitFighters[i] = new UnitFighter(_layer, _id, baseData.troopModel, baseData.moveSpeed);
    }

    baseMat = new Material(t);
    baseMat -> setColor(255, 255, 255, 255);

    damagedMat = new Material(t);
    damagedMat -> setColor(255, 255, 0, 0);

    setBaseMaterial();
}

Unit::~Unit() {
    WorldGeometry::Instance()->clearUnitCell(getPosition(), this);
    delete lookForTargetTimer;
    delete pathManager;
    for(std::size_t i = 0; i < unitFighters.size(); i++){
        delete unitFighters[i];
    }
    unitFighters.clear();
    delete recruitingTimer;
}

void Unit::Init() {
    //ToDo: esto ya no es necesario
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
            //ToDo: inHomeState();
        break;
        case Enumeration::UnitState::Idle:
            //ToDo: poner material idle
            idleState();
        break;
        case Enumeration::UnitState::Move:
            //ToDo: poner material moving
            moveState();
        break;
        case Enumeration::UnitState::AttackMove:
            //ToDo: poner material attackMove
            attackMoveState();
        break;
        case Enumeration::UnitState::Attack:
            //ToDo: poner material attack
            attackState();
        break;    
        case Enumeration::UnitState::Chase:
            //s//ToDo: poner material chase
            chaseState();
        break;
        case Enumeration::UnitState::Retract:
            ////ToDo: poner material retracting
            retractState();
        break;
        default: break;
    }
}

void Unit::preTaxPlayer() {
    if (getTeam() == Enumeration::Team::Human) {
        Human::Instance() -> spendResources(getMetalCost(), getCrystalCost());
        Human::Instance() -> increaseHappiness(getHappinessVariation());
        Human::Instance() -> increaseCitizens(getCitizensVariation());
        Human::Instance() -> increaseArmyLevel(armyLevel);
    } else {
        IA::Instance() -> spendResources(getMetalCost(), getCrystalCost());
        IA::Instance() -> increaseHappiness(getHappinessVariation());
        IA::Instance() -> increaseCitizens(getCitizensVariation());
        IA::Instance() -> increaseArmyLevel(armyLevel);
    }
}

void Unit::posTaxPlayer(){
    if (getTeam() == Enumeration::Team::Human) {
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
    recruitingTimer -> tick();
    if (recruitingTimer -> isRunning()){
        if (getTeam() == Enumeration::Team::Human){
            Hud::Instance() -> modifyTroopFromQueue(getID(), recruitingTimer -> getElapsedTime() / recruitingTimer -> getMaxDuration());
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
    if (getTarget() != nullptr) {
        Vector2<f32> tpos = Vector2<f32>();
        tpos.x = getTarget() -> getPosition().x;
        tpos.y = getTarget() -> getPosition().y;
        this  -> setTroopDestination(tpos);
        chaseTarget();    
    }
}

void Unit::retractState() {
    moveTroop();
    if (readyToEnter){
        retractedCallback(this);
        //troops -> setActive(false);
        getModel() -> setActive(false);
        switchState(Enumeration::UnitState::InHome);
        // ToDo: Aqui peta
        triggerRetractedCallback();        
    }
}
/* ToDo: delta time */
void Unit::moveTroop() {
    std::cout << "Esto en:" << getPosition().x << "," << getPosition().y << "\n";
    if(team == 0){
        std::cout << "Soy humano \n";
    }
    else{
        std::cout << "Soy ia \n";
    }
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
                //Vector2<f32> newDest = this->pathFollow.front();
                //Vector2<f32> newDest(dummy.x, dummy.y);
                //setTroopDestination(newDest);
                setTroopDestination(this->pathFollow.front());
                pathFollow.pop_front();
            }
        }
        // Update Cell state 
        else if(std::floor(steps) == 0){
            Vector2<f32> newPos = vectorPos + vectorMov;
            WorldGeometry::Instance()->updateUnitCell(vectorPos, newPos, this);
            
            //std::vector< Unit* > nearUnits = WorldGeometry::Instance()->getNeighborUnits(newPos);
            //std::vector< Vector2<f32> > nearTroopsPosition;
            //for(int i = 0; i < nearUnits.size(); i++){
            //    nearTroopsPosition.insert(nearTroopsPosition.end(), nearUnits[i]->getTroopsPosition().begin(), nearUnits[i]->getTroopsPosition().end());
            //}
            setPosition(newPos);
            steps = 0;
            //std::cout << "Voy pa:" << newPos.x << "," << newPos.y << "\n";
        } 
        else {
            Vector2<f32> newPos = vectorPos + vectorMov;
            WorldGeometry::Instance()->updateUnitCell(vectorPos, newPos, this);

            //std::vector< Unit* > nearUnits = WorldGeometry::Instance()->getNeighborUnits(newPos);
            
            setPosition(newPos);
            //troops -> moveTroops(vectorMov);

            steps--;
            //std::cout << "Voy pa:" << newPos.x << "," << newPos.y << "\n";
        }
        for(std::size_t i = 0; i < unitFighters.size(); i++){
            unitFighters[i]->update();
        }
    }
}

void Unit::attack() {
    if (getTarget() != nullptr && getTarget() -> getTeam() != getTeam()) {
        setAttacking(true);
        if (attackCountdown <= 0) {
            getTarget() -> takeDamage(attackDamage);
            attackCountdown = attackSpeed;
            if (getTarget() -> getCurrentHP() <= 0) {
                if (getTarget() -> getTarget() != nullptr) {
                    getTarget() -> getTarget() -> removeHostile(getTarget());
                }
                if (getTeam() == Enumeration::Team::Human) {
                    if (getTarget() -> getEntityType() == Enumeration::EntityType::Unit) {
                        IA::Instance() -> getUnitManager() -> deleteUnit(getTarget() -> getID());
                    } else {
                        IA::Instance() -> getBuildingManager() -> deleteBuilding(getTarget() -> getID());
                    }
                } else {
                    if (getTarget() -> getEntityType() == Enumeration::EntityType::Unit) {
                        Human::Instance() -> getUnitManager() -> deleteUnit(getTarget() -> getID());
                    } else {
                        Human::Instance() -> getBuildingManager() -> deleteBuilding(getTarget() -> getID());
                    }
                }
                setTarget(nullptr);
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
            Vector2<f32> newPos = getPosition() + vectorMov;
            //newPos.y = Map::Instance() -> getTerrain() -> getY(newPos.x, newPos.z);
            setTroopPosition(newPos);
        }
    }
}

/* Edit this */
bool Unit::inRangeOfAttack() {
    bool inRange = false;
    if (getTarget() != nullptr) {
        f32 xaux = getTarget()->getPosition().x - this->getPosition().x;
        f32 yaux = getTarget()->getPosition().y - this->getPosition().y;
        f32 dist = sqrtf(pow(xaux, 2) - pow(yaux, 2));
        if (dist <= getAttackRange()) {
            inRange = true;
        }
    }
    return inRange;
}

bool Unit::refreshTarget() {
    bool targetUpdated = false;
    lookForTargetTimer -> tick();
    // return wether or not it got updated
    if (getTarget() != nullptr) {
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
/* Weird method */
void Unit::setTroopPosition(Vector2<f32> vectorData) {
    //vectorPos.set(vectorData);
    //vectorPos = vectorData;
    setPosition(vectorData);
    for(std::size_t i = 0; i < unitFighters.size(); i++){
        unitFighters[i]->setPosition(vectorData);
    }
}
// To do -> adjust units movement
void Unit::setTroopDestination(Vector2<f32> vectorData) {
    if (state == Enumeration::UnitState::Move) {
        setTarget(nullptr);
    }
    //vectorDes.set(vectorData);
    vectorDes = vectorData;
    Vector2<f32> desp = vectorDes - getPosition();
    f32 distance = std::sqrt(std::pow(desp.x, 2) + std::pow(desp.y, 2));
    //vectorMov -> x = (desp.x / distance) * moveSpeed * Game::Instance() -> getWindow() -> getDeltaTime();
    //vectorMov -> z = (desp.z / distance) * moveSpeed * Game::Instance() -> getWindow() -> getDeltaTime();
    vectorMov.x = (desp.x / distance) * (moveSpeed / 100);
    vectorMov.y = (desp.y / distance) * (moveSpeed / 100);
    f32 movDistance = std::sqrt(std::pow(vectorMov.x, 2) + std::pow(vectorMov.y, 2));
    steps = distance / movDistance;
    for(std::size_t i = 0; i < unitFighters.size(); i++){
        unitFighters[i]->setDestiny(vectorData);
    }
    /*vectorDes.set(vectorData);
    Vector3<f32> desp = vectorDes - vectorPos;
    f32 distance = std::sqrt(std::pow(desp.x, 2) + std::pow(desp.z, 2));
    vectorMov.x = (desp.x / distance) * (moveSpeed / 100);
    vectorMov.z = (desp.z / distance) * (moveSpeed / 100);
    f32 movDistance = std::sqrt(std::pow(vectorMov.x, 2) + std::pow(vectorMov.z, 2));
    steps = (distance / movDistance);*/
    moving = true;
}

void Unit::setPath(std::list< Vector2<f32> > path){
    this->pathFollow = path;
}

void Unit::setPathToTarget(Vector2<f32> vectorData){
    std::cout << "Analizando camino \n";
    this->pathManager->createPathTo(vectorData);
    if(!pathFollow.empty()){
        //Vector2<f32> dummy = this->pathFollow.front();
        //Vector2<f32> newDest;
        //newDest.x = dummy.x;
        //newDest.y = Map::Instance() -> getTerrain() -> getY(dummy.x, dummy.y);
        //newDest.y = dummy.y;
        setTroopDestination(this->pathFollow.front());
        std::cout << "Lo tengo " << pathFollow.size() << "\n";
        pathFollow.pop_front();
        std::cout << "Salgo ya " << "\n";
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

Vector2<f32> Unit::getDestination() {
    return vectorDes;
}

std::list< Vector2<f32> > Unit::getPath(){
    return pathFollow;
}

std::string Unit::getType(){
    return type;
}

Enumeration::UnitState Unit::getState() {
    return state;
}

i32 Unit::getArmyLevel(){
    return armyLevel;
}