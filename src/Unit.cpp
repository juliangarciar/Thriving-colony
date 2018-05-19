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
#include "Game.h"
#include "Sensor.h"
#include "IOEngine/IO.h"
#include "UnitManager.h"

//ToDo: revisar y limpiar esta clase

Unit::Unit(SceneNode* _layer, 
    i32 _id, 
    Enumeration::Team _team, 
    UnitData baseData,
    UnitManager* _unitManager):Entity(
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
                            moving(false),
                            canAttack(true),
                            armyLevel(baseData.armyLevel),
                            pathManager(nullptr),
                            pathFollow(),
                            vectorDes(0,0),
                            vectorSpd(0,0),
                            readyToEnter(false),
                            attackEvent(baseData.attackEvent),
                            moveEvent(baseData.moveEvent),
                            selectEvent(baseData.selectEvent),
                            unitFighters(baseData.troops, nullptr),
                            maxPositionDesviation(baseData.moveSpeed * 0.5f),
                            unitFighterHP(baseData.maxHP / baseData.troops),
                            unitSensor(nullptr),
                            unitManager(_unitManager)      
{

    unitSensor = new Sensor(this);

    recruitingTimer = new Timer(baseData.recruitingTime, false);
    recruitingTimer -> setCallback([&](){
        recruitedCallback(this);
        switchState(Enumeration::UnitState::InHome);
    });

    enemySensorTimer = new Timer(0.5, true, true);
    enemySensorTimer->setCallback([&](){
        //if(state != Enumeration::UnitState::InHome && state != Enumeration::UnitState::Recruiting){
            unitSensor->update();
        //}
    });

    attackTimer = new Timer(attackSpeed, true, true);
    attackTimer->setCallback([&](){
        //if(!canAttack){
            canAttack = true;
        //}
    });

    chaseTimer = new Timer(0.5, false, false);
    chaseTimer->setCallback([&](){
        if(target != nullptr){
            setPathToTarget(target->getPosition());
        }
    });

    pathManager = new PathManager(this);

    for(std::size_t i = 0; i < unitFighters.size(); i++){
        unitFighters[i] = new UnitFighter(_layer, _id, baseData.troopModel, baseData.moveSpeed);
    }
}

Unit::~Unit() {
    WorldGeometry::Instance()->clearUnitCell(getPosition(), this);
    for(std::size_t i = 0; i < unitFighters.size(); i++){
        delete unitFighters[i];
    }
    unitFighters.clear();
    delete unitSensor;
    delete pathManager;

    delete recruitingTimer;
    delete enemySensorTimer;
    delete attackTimer;
    delete chaseTimer;
}

void Unit::Init() {
    //ToDo: esto ya no es necesario
    preTaxPlayer();
}

void Unit::update() {
    //returnToOriginalColor(); //ToDo: daba segfault aqui en el arbol very unhappy
    //State machine, color changes according to state
    updateUnitFighters();
    moveTroop();
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
        /* Maybe this shouldn't exist */
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
        Human::Instance() -> modifyHappiness(getHappinessVariation());
        Human::Instance() -> modifyCitizens(getCitizensVariation());
        Human::Instance() -> modifyArmyLevel(armyLevel);
    } else {
        IA::Instance() -> spendResources(getMetalCost(), getCrystalCost());
        IA::Instance() -> modifyHappiness(getHappinessVariation());
        IA::Instance() -> modifyCitizens(getCitizensVariation());
        IA::Instance() -> modifyArmyLevel(armyLevel);
    }
}

void Unit::switchState(Enumeration::UnitState newState) {
    state = newState;
}

void Unit::recruitingState() {
    if (recruitingTimer -> isRunning()) {
        if (getTeam() == Enumeration::Team::Human) {
            Hud::Instance() -> modifyTroopFromQueue(getID(), recruitingTimer -> getElapsedTime() / recruitingTimer -> getMaxDuration());
        }
    }
}

void Unit::idleState() {
    if (target != nullptr) {
        switchState(Enumeration::UnitState::Attack);
    }
}

/* ToDo: Este estado es inutil en realidad, comprobar su utilidad */
void Unit::moveState() {
}

/* ToDo: Tenemos que hablar si existen shortcuts para llamar este */
void Unit::attackMoveState() {
}

void Unit::attackState() {
    if(target != nullptr){
        if(inRangeOfAttack()) {
            if(canAttack){
                target->takeDamage(attackDamage);
                canAttack = false;
            }
        }
        else{
            switchState(Enumeration::UnitState::Chase);
            setPathToTarget(target->getPosition());
            chaseTimer->restart();
        }
    }
    else{
        switchState(Enumeration::UnitState::Idle);
        enemySensorTimer->restart();
    }
}

// Chasing the target
void Unit::chaseState() {
    if(target == nullptr){
        switchState(Enumeration::UnitState::Idle);
        chaseTimer->stop();
        enemySensorTimer->restart();
    }
    else{
        if(inRangeOfAttack()) {
            switchState(Enumeration::UnitState::Attack);
            chaseTimer->stop();
        }
    }
}

void Unit::retractState() {
    if (readyToEnter){
        retractedCallback(this);
        for(std::size_t i = 0; i < unitFighters.size(); ++i){
            unitFighters[i] -> setActive(false);
        }
        getModel() -> setActive(false);
        switchState(Enumeration::UnitState::InHome);
        // ToDo: Aqui peta
        //triggerRetractedCallback();        
    }
}

void Unit::moveTroop() {
    if (moving) {
        // close to destination, stop
        if (hasArrived()) {
            if (pathFollow.empty()) {
                moving = false;
                if (state == Enumeration::UnitState::Retract) {
                    readyToEnter = true;
                    Human::Instance() -> getUnitManager() -> unSelectTroop();
                    //triggerRetractedCallback();
                }
                else if(state == Enumeration::UnitState::Chase){
                    switchState(Enumeration::UnitState::Attack);
                    chaseTimer->stop();
                }
                else{
                    switchState(Enumeration::UnitState::Idle);
                    enemySensorTimer->restart();
                }
            }
            else{
                setTroopDestination(this->pathFollow.front());
                pathFollow.pop_front();
            }
        }
        else{
            calculateDirection();
            Vector2<f32> _oldPosition = vectorPos;
            vectorSpd = vectorDir * moveSpeed;
            vectorPos += vectorSpd;
            vectorPos = _oldPosition + (vectorPos - _oldPosition) * Window::Instance() -> getDeltaTimeVariance();
            WorldGeometry::Instance() -> updateUnitCell(_oldPosition, vectorPos, this);
            setPosition(vectorPos);
            unitSensor -> move(vectorPos);
        }
    }
}

/* Edit this */
bool Unit::inRangeOfAttack() {
    bool inRange = false;
    if (getTarget() != nullptr) {
        f32 xaux = getTarget() -> getPosition().x - getPosition().x;
        f32 yaux = getTarget() -> getPosition().y - getPosition().y;
        f32 dist = sqrtf(pow(xaux, 2) - pow(yaux, 2));
        if (dist <= getAttackRange()) {
            inRange = true;
        }
    }
    return inRange;
}

void Unit::triggerRecruitedCallback(){
    recruitedCallback(this);
}

void Unit::triggerRetractedCallback() {
    retractedCallback(this);
}

/////SETTERS/////
void Unit::setUnitCell(Vector2<f32> vectorPosition) {
    WorldGeometry::Instance() -> setUnitCell(vectorPosition, this);
}

void Unit::setUnitPosition(Vector2<f32> vectorData) {
    setPosition(vectorData);
    std::size_t size = unitFighters.size();
    for(std::size_t i = 0; i < size; i++){
        unitFighters[i]->setPosition(vectorData + WorldGeometry::Instance()->getSquadPosition(size - 1, i));
    }
}

void Unit::setTroopDestination(Vector2<f32> _vectorData) {
    /* Esto que es */
    if (state == Enumeration::UnitState::Move) {
        setTarget(nullptr);
    }

    vectorDes = _vectorData;
    std::size_t size = unitFighters.size();
    for (std::size_t i = 0; i < size; i++) {
        unitFighters[i] -> setDestiny(_vectorData + WorldGeometry::Instance() -> getSquadPosition(size - 1, i));
    }
    moving = true;
}

void Unit::setPath(std::list<Vector2<f32>> path) {
    pathFollow = path;
}

void Unit::setPathToTarget(Vector2<f32> vectorData) {
    pathManager -> createPathTo(vectorData);
    if (!pathFollow.empty()) {
        setTroopDestination(pathFollow.front());
        pathFollow.pop_front();
    }
}

void Unit::setRecruitedCallback(std::function<void(Unit*)> f) {
    recruitedCallback = f;
}

void Unit::setRetractedCallback(std::function<void(Unit*)> f) {
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

std::list<Vector2<f32>> Unit::getPath() {
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

std::vector<UnitFighter*> Unit::getUnitFighters() {
    return unitFighters;
}

void Unit::calculateDirection() {
    Vector2<f32> _incVector = vectorDes - vectorPos;
    /* Normalize */
    f32 distance = std::sqrt(std::pow(_incVector.x, 2) + std::pow(_incVector.y ,2));
    
    if(distance != 0){
        vectorDir = _incVector / distance;        
    }   
    else{
        vectorDir = Vector2<f32>(0, 0);
    }
}
bool Unit::hasArrived() {
    if ((vectorPos - vectorDes).dotProduct() < maxPositionDesviation) {
        vectorSpd = Vector2<f32>(0, 0);
        return true;
    }
    return false;
}
/* Check how to do this */
void Unit::updateFlockingSensor() {
    std::vector<Unit*> nearUnits = WorldGeometry::Instance() -> getNeighborUnits(vectorPos);
    std::vector<UnitFighter*> dummyFighters;
    std::vector<UnitFighter*> dummySpace;
    for(std::size_t i = 0; i < nearUnits.size(); i++) {
        dummySpace = nearUnits[i] -> getUnitFighters();
        dummyFighters.insert(dummyFighters.end(), dummySpace.begin(), dummySpace.end());
    }
    nearUnitFighters = dummyFighters;
    for(std::size_t i = 0; i < unitFighters.size(); i++){
        unitFighters[i] -> setNearFighters(nearUnitFighters);
    }
}

void Unit::takeDamage(i32 _damage){
    
    i32 resistance = 0;
    if (team == Enumeration::Team::Human) {
        resistance = Human::Instance() -> getResistanceModifier();
    } 
    else {
        resistance = IA::Instance() -> getResistanceModifier();
    }
    i32 dmg = _damage - resistance;

    if (dmg < 0) {
        dmg = 0;
    }
    currentHP = currentHP - dmg;
    tookDamageTimer -> restart();
    setDamageColor();
    if (currentHP <= 0) {
        currentHP = 0;
        unitManager->deleteUnit(ID);
        return;
    }
    else{
        i32 _qnty = std::floor(currentHP / unitFighterHP);
        if(currentHP % unitFighterHP != 0){
            _qnty++;
        }
        while(_qnty < unitFighters.size()){
            UnitFighter* tmp = unitFighters[unitFighters.size() - 1];
            unitFighters.erase(unitFighters.end() - 1);
            delete tmp;
        }
        tookDamageTimer -> restart();
        setDamageColor();
    }
}

void Unit::updateUnitFighters() {
    updateFlockingSensor();
    for (std::size_t i = 0; i < unitFighters.size(); i++) {
        unitFighters[i] -> update();
    }
}

void Unit::setTarget(Entity *newTarget) {
    target = newTarget;
    if (target == nullptr) {
        switchState(Enumeration::UnitState::Idle);
        enemySensorTimer->restart();
    }
    else{
        switchState(Enumeration::UnitState::Attack);
    }
}