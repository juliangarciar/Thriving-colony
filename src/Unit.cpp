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
    UnitManager* _unitManager) :Entity(_layer,
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
                                        baseData.cellsX,
                                        baseData.cellsY,
                                        baseData.flagModel,
                                        baseData.bbOffset
                                    ),
                                    state(Enumeration::UnitState::Recruiting),
                                    type(baseData.type),
                                    building(baseData.buildingType),
                                    moveSpeed(baseData.moveSpeed),
                                    attackSpeed(baseData.attackSpeed),
                                    attackDamage(baseData.attackDamage),
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
    recruitingTimer -> setCallback([&]() {
        if (recruitedCallback) recruitedCallback(this);
        switchState(Enumeration::UnitState::InHome);
    });

    enemySensorTimer = new Timer(0.5, true, false);
    enemySensorTimer -> setCallback([&]() {
        if (state != Enumeration::UnitState::InHome && state != Enumeration::UnitState::Recruiting) {
            unitSensor->update();
        }
    });
    attackTimer = new Timer(attackSpeed, false, false);
    attackTimer -> setCallback([&]() {
        canAttack = true;
    });

    chaseTimer = new Timer(0.5, true, false);
    chaseTimer -> setCallback([&]() {
        if (target != nullptr) {
            setPathToTarget(target -> getPosition());
        }
    });

    pathManager = new PathManager(this);

    for(std::size_t i = 0; i < unitFighters.size(); i++){
        unitFighters[i] = new UnitFighter(_layer, this, baseData.troopModel, baseData.moveSpeed, baseData.attackRange, i);
    }
}

Unit::~Unit() {
    WorldGeometry::Instance()->clearUnitCell(getPosition(), this);
    for (std::size_t i = 0; i < unitFighters.size(); i++) {
        unitManager->adjustUnitFighter(-1);
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

void Unit::preTaxPlayer() {
    if (getTeam() == Enumeration::Team::Human) {
        Human::Instance() -> spendResources(getMetalCost(), getCrystalCost());
        Human::Instance() -> modifyHappiness(getHappinessVariation());
        Human::Instance() -> modifyCitizens(-getCitizensVariation());
        Human::Instance() -> modifyArmyLevel(armyLevel);
    } else {
        IA::Instance() -> spendResources(getMetalCost(), getCrystalCost());
        IA::Instance() -> modifyHappiness(getHappinessVariation());
        IA::Instance() -> modifyCitizens(-getCitizensVariation());
        IA::Instance() -> modifyArmyLevel(armyLevel);
    }
}

void Unit::update() {
    updateUnitFighters();
    switch (state) {
        case Enumeration::UnitState::Recruiting:
            recruitingState();
        break;

        case Enumeration::UnitState::InHome:
            inHomeState();
        break;

        case Enumeration::UnitState::Idle:
            idleState();
        break;

        case Enumeration::UnitState::Move:
            moveState();
        break;

        case Enumeration::UnitState::AttackMove:
            attackMoveState();
        break;

        case Enumeration::UnitState::Attack:
            attackState();
        break;   

        case Enumeration::UnitState::Chase:
            chaseState();
        break;

        case Enumeration::UnitState::Retract:
            retractState();
        break;

        default: 
            std::cout << "ERROR UNIT STATE \n";
        break;
    }
}

void Unit::switchState(Enumeration::UnitState newState) {
    switch (newState) {
        case Enumeration::UnitState::Recruiting:
            state = newState;
        break;

        case Enumeration::UnitState::InHome:
            chaseTimer->stop();
            enemySensorTimer->stop();
            switchUnitFigthersState(Enumeration::UnitFighterState::ufIdle);
            state = newState;
        break;

        case Enumeration::UnitState::Idle:
            chaseTimer->stop();
            enemySensorTimer->restart();
            state = newState;
        break;

        case Enumeration::UnitState::Move:
            chaseTimer->stop();
            enemySensorTimer->stop();
            switchUnitFigthersState(Enumeration::UnitFighterState::ufMove);
            state = newState;
        break;

        case Enumeration::UnitState::AttackMove:
            chaseTimer->stop();
            enemySensorTimer->restart();
            state = newState;
        break;

        case Enumeration::UnitState::Attack:
            chaseTimer->stop();
            enemySensorTimer->stop();
            switchUnitFigthersState(Enumeration::UnitFighterState::ufConfront);
            state = newState;
        break;   

        case Enumeration::UnitState::Chase:
            chaseTimer->restart();
            enemySensorTimer->stop();
            switchUnitFigthersState(Enumeration::UnitFighterState::ufMove);
            state = newState;
        break;

        case Enumeration::UnitState::Retract:
            chaseTimer -> stop();
            enemySensorTimer -> stop();
            switchUnitFigthersState(Enumeration::UnitFighterState::ufMove);
            state = newState;
        break;

        default: 
            std::cout << "INVALID UNIT STATE \n";
        break;
    }
}

void Unit::recruitingState() {
    if (recruitingTimer -> isRunning()) {
        if (getTeam() == Enumeration::Team::Human) {
            Hud::Instance() -> modifyTroopFromQueue(getID(), recruitingTimer -> getElapsedTime() / recruitingTimer -> getMaxDuration());
        }
    }
}

/* Nothing? */
void Unit::inHomeState() {
    
}

void Unit::idleState() {
    if (target != nullptr) {
        switchState(Enumeration::UnitState::Attack);
    }
}

void Unit::moveState() {
    moveUnit();
}

/* ToDo: Tenemos que hablar si existen shortcuts para llamar este */
/* End this method */
void Unit::attackMoveState() {
    moveUnit();
}

void Unit::attackState() {
    if (target != nullptr) {
        if (inRangeOfAttack()) {
            if (canAttack) {
                target -> takeDamage(attackDamage);
                canAttack = false;
                attackTimer -> restart();
            }
        }
        else {
            switchState(Enumeration::UnitState::Chase);
            setPathToTarget(target -> getPosition());
            moveUnit();
        }
    }
    else {
        switchState(Enumeration::UnitState::Idle);
    }
}

void Unit::chaseState() {
    if (target == nullptr) {
        switchState(Enumeration::UnitState::Idle);
    }
    else {
        if (inRangeOfAttack()) {
            switchState(Enumeration::UnitState::Attack);
        }
        else {
            moveUnit();
        }
    }
}

void Unit::retractState() {
    if (readyToEnter) {
        if (retractedCallback) retractedCallback(this);
        for (std::size_t i = 0; i < unitFighters.size(); ++i) {
            unitFighters[i] -> setActive(false);
        }
        getModel() -> setActive(false);
        switchState(Enumeration::UnitState::InHome);
        // ToDo: Aqui peta
        //triggerRetractedCallback();        
    }
    else {
        moveUnit();
    }
}

void Unit::moveUnit() {
    if (hasArrived()) {
        if (pathFollow.empty()) {
            if (state == Enumeration::UnitState::Retract) {
                readyToEnter = true;
                Human::Instance() -> getUnitManager() -> unSelectTroop();
                switchState(Enumeration::UnitState::InHome);
                //triggerRetractedCallback();
            }
            else if (state == Enumeration::UnitState::Chase) {
                switchState(Enumeration::UnitState::Attack);
            }
            else {
                switchState(Enumeration::UnitState::Idle);
            }
        } else {
            setUnitDestination(pathFollow.front());
            pathFollow.pop_front();
        }
    } else {
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

void Unit::triggerRecruitedCallback() {
    if (recruitedCallback) recruitedCallback(this);
}

void Unit::triggerRetractedCallback() {
    if (retractedCallback) retractedCallback(this);
}

void Unit::setUnitCell(Vector2<f32> vectorPosition) {
    WorldGeometry::Instance() -> setUnitCell(vectorPosition, this);
}

void Unit::setUnitPosition(Vector2<f32> vectorData) {
    setPosition(vectorData);
    std::size_t size = unitFighters.size();

    for (std::size_t i = 0; i < size; i++) {
        unitFighters[i] -> setPosition(vectorData + WorldGeometry::Instance()->getSquadPosition(size - 1, i));
    }
}

void Unit::setUnitDestination(Vector2<f32> _vectorData) {
    if (state == Enumeration::UnitState::Move) {
        target = nullptr;
    }

    if (target == nullptr) {
        vectorFinalDestiny = vectorDes;
    }

    vectorDes = _vectorData;
    std::size_t size = unitFighters.size();

    for (std::size_t i = 0; i < size; i++) {
        unitFighters[i] -> setDestiny(_vectorData + WorldGeometry::Instance() -> getSquadPosition(size - 1, i));
    }
}

void Unit::setPath(const std::list< Vector2<f32> >& path) {
    pathFollow = path;
}

void Unit::setPathToTarget(Vector2<f32> vectorData) {
    pathManager -> createPathTo(vectorData);
    if (!pathFollow.empty()) {
        setUnitDestination(pathFollow.front());
        pathFollow.pop_front();
    }
}

void Unit::setRecruitedCallback(std::function<void(Unit*)> f) {
    recruitedCallback = f;
}

void Unit::setRetractedCallback(std::function<void(Unit*)> f) {
    retractedCallback = f;
}

void Unit::takeDamage(i32 _damage) {
    i32 resistance(0);
    f32 percentage(0);

    if (team == Enumeration::Team::Human) {
        resistance = Human::Instance() -> getResistanceModifier();
    } else {
        resistance = IA::Instance() -> getResistanceModifier();
    }

    i32 dmg = _damage - resistance;

    if (dmg < 0) {
        dmg = 0;
    }

    currentHP = currentHP - dmg;
    
    tookDamageTimer -> restart();
    setDamageColor();
    if (currentHP < 1) {
        for (std::size_t i = 0; i < hostile.size(); i++) {
            Unit* aux = (Unit*)hostile[i];
            aux -> setUnitDestination(aux -> getFinalDestination());
        }
        unitManager->deleteUnit(ID);
        return;
    } else {
        percentage = (float)currentHP / (float)maxHP;
		bar->setFrontWidth(percentage);
		bar->setFrontColor(Color(1.f-percentage, percentage, 0));
        i32 _qnty = std::floor(currentHP / unitFighterHP);
        if (currentHP % unitFighterHP != 0) {
            _qnty++;
        }
        while(_qnty < unitFighters.size()) {
            unitManager->adjustUnitFighter(-1);
            UnitFighter* tmp = unitFighters[unitFighters.size() - 1];
            unitFighters.erase(unitFighters.end() - 1);
            delete tmp;
        }
    }
}

void Unit::setTarget(Entity *newTarget) {
    target = newTarget;
    if (target == nullptr) {
        switchState(Enumeration::UnitState::Idle);
    }
    else{
        target->addHostile(this);
        switchState(Enumeration::UnitState::Attack);
    }
}

bool Unit::inRangeOfAttack() {
    bool inRange = false;
    if(target != nullptr){
        Vector2<f32> tmp(target->getPosition() - vectorPos);
        f32 distance = std::sqrt(std::pow(tmp.x, 2) + 
                                 std::pow(tmp.y, 2));

        distance = distance - target->getHitbox().getRadius() - this->getHitbox().getRadius();
        if( distance <= attackRange){
            inRange = true;
        }
    }
    return inRange;
}

const string Unit::getAttackEvent() const{
    return attackEvent;
}

const string Unit::getMoveEvent() const{
    return moveEvent;
}

const string Unit::getSelectEvent() const{
    return selectEvent;
}

Vector2<f32> Unit::getDestination() const{
    return vectorDes;
}

Vector2<f32> Unit::getFinalDestination() const {
    return vectorFinalDestiny;
}

const std::list< Vector2<f32> >& Unit::getPath() const{
    return pathFollow;
}

const std::string Unit::getType() const{
    return type;
}

const std::string Unit::getBuildingName() const{
	return building;
}

Enumeration::UnitState Unit::getState() const{
    return state;
}

const i32 Unit::getArmyLevel() const{
    return armyLevel;
}

std::vector< Vector2<f32> > Unit::getInnerComponentsPosition() const{
    std::vector< Vector2<f32> > dummy;
    for(std::size_t i = 0; i < unitFighters.size(); ++i){
        dummy.push_back(unitFighters[i]->getVectorPosition());
    }
    return dummy;
}

const std::vector< UnitFighter* >& Unit::getUnitFighters() const{
    return unitFighters;
}

bool Unit::hasArrived() {
    if ((vectorPos - vectorDes).dotProduct() < maxPositionDesviation) {
        vectorSpd = Vector2<f32>(0, 0);
        return true;
    }
    return false;
}

void Unit::calculateDirection() {
    Vector2<f32> _incVector = vectorDes - vectorPos;
    /* Normalize */
    f32 distance = std::sqrt(std::pow(_incVector.x, 2) + std::pow(_incVector.y ,2));
    
    if (distance != 0) {
        vectorDir = _incVector / distance;        
    }   
    else {
        vectorDir = Vector2<f32>(0, 0);
    }
}

void Unit::updateUnitFighters() {
    updateFlockingSensor();
    for (std::size_t i = 0; i < unitFighters.size(); i++) {
        unitFighters[i] -> update();
    }
}

void Unit::updateFlockingSensor() {
    std::vector<Unit*> nearUnits = WorldGeometry::Instance() -> getNeighborUnits(vectorPos);
    std::vector<UnitFighter*> dummyFighters;
    std::vector<UnitFighter*> dummySpace;
    for (std::size_t i = 0; i < nearUnits.size(); i++) {
        dummySpace = nearUnits[i] -> getUnitFighters();
        dummyFighters.insert(dummyFighters.end(), dummySpace.begin(), dummySpace.end());
    }
    nearUnitFighters = dummyFighters;
    for (std::size_t i = 0; i < unitFighters.size(); i++) {
        unitFighters[i] -> setNearFighters(nearUnitFighters);
    }
}

void Unit::switchUnitFigthersState(Enumeration::UnitFighterState _state){
    for(std::size_t i = 0; i < unitFighters.size(); ++i){
        unitFighters[i]->switchState(_state);
    }
}