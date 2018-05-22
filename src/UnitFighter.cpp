#include "UnitFighter.h"
#include "MathEngine/Vector3.h"
#include "Map.h"
#include "GraphicEngine/Window.h"
#include "IOEngine/Timer.h"
#include "IOEngine/IO.h"
#include "Entity.h"

UnitFighter::UnitFighter(SceneNode* _parent, 
                        Unit* _unitLeader, 
                        std::string _path, 
                        f32 _speed, 
                        f32 _attackRange, 
                        i32 _fighterIndex):unitLeader(_unitLeader),
                                            speed(_speed), 
                                            attackRange(_attackRange),
                                            fighterIndex(_fighterIndex),
                                            vectorPosition(0, 0),
                                            vectorSpeed(0, 0),
                                            vectorDestiny(0, 0),
                                            vectorDirection(0, 0),
                                            maxDesviation(_speed * 0.5f), 
                                            maxTime(0), 
                                            unitFighterClock(nullptr), 
                                            nearFighters(std::vector< UnitFighter* >()),
                                            fighterState(Enumeration::UnitFighterState::ufIdle)                                                                                                            
{
    fighterModel = new Animation(_parent, _path);
    
    unitFighterClock = new Timer(1, false, false);
    unitFighterClock->setCallback([&]{
        /* Stop movement */
        if(fighterState == Enumeration::UnitFighterState::ufMove){
            switchState(Enumeration::UnitFighterState::ufIdle);
        }
        else if(fighterState == Enumeration::UnitFighterState::ufConfront){
            switchState(Enumeration::UnitFighterState::ufAttack);
        }
    });

    rotationClock = new Timer(0.1, true, false);
    rotationClock->setCallback([&]{
        //std::cout << "Estoy rotando bitch \n";
        rotateFighter();
    });
}

UnitFighter::~UnitFighter(){
    delete unitFighterClock;
    delete rotationClock;
    delete fighterModel;
    nearFighters.clear();
}

void UnitFighter::setPosition(Vector2<f32> _pos) {
    vectorPosition = _pos;
    fighterModel->setPosition(Vector3<f32>(_pos.x, Map::Instance()->getTerrain()->getY(_pos.x, _pos.y), _pos.y));
}

void UnitFighter::setDestiny(Vector2<f32> _dest){
    if(fighterState == Enumeration::UnitFighterState::ufIdle){
        switchState(Enumeration::UnitFighterState::ufMove);
    }
    //calculateDirection();
    /* Put here the flocking and rotation */
    vectorDestiny = _dest;
    Vector2<f32> vectorDistance = (vectorDestiny - vectorPosition);
    maxTime = (std::sqrt(std::pow(vectorDistance.x, 2) + std::pow(vectorDistance.y, 2))) / speed * 0.016f ;
    maxTime += 0.15f * maxTime;
    unitFighterClock->changeDuration(maxTime);
    unitFighterClock->restart();
}

void UnitFighter::move(){
    calculateDirection();
    Vector2<f32> _oldPosition = vectorPosition;
    vectorSpeed = vectorDirection * speed;
    vectorPosition += vectorSpeed;
    vectorPosition = _oldPosition + (vectorPosition - _oldPosition) * Window::Instance()->getDeltaTimeVariance();
    fighterModel->setPosition(Vector3<f32>(vectorPosition.x, Map::Instance()->getTerrain()->getY(vectorPosition.x, vectorPosition.y), vectorPosition.y));
}

void UnitFighter::update() {
    switch(fighterState) {
        case Enumeration::UnitFighterState::ufAttack:
            ufAttackState();
        break;

        case Enumeration::UnitFighterState::ufMove:
            ufMoveState();
        break;

        case Enumeration::UnitFighterState::ufIdle:
            ufIdleState();
        break;

        case Enumeration::UnitFighterState::ufConfront:
            ufConfrontState();
        break;
    
        default: 
            std::cout << "INVALID FIGHTER STATE \n";
        break;
    }
}

void UnitFighter::switchState(Enumeration::UnitFighterState _state) {
    switch(_state) {
        case Enumeration::UnitFighterState::ufAttack:
            unitFighterClock->stop();
            if(fighterState != Enumeration::UnitFighterState::ufAttack){
                calculateDirection();
                fighterModel->changeAnimation("attack");
				fighterModel->setRandomFrame();
                fighterState = _state;
            }
        break;

        case Enumeration::UnitFighterState::ufMove:
            if(fighterState != Enumeration::UnitFighterState::ufMove){
                fighterModel->changeAnimation("walk");
				fighterModel->setRandomFrame();
                fighterState = _state;
            }
        break;

        case Enumeration::UnitFighterState::ufIdle:
            unitFighterClock->stop();
            if(fighterState != Enumeration::UnitFighterState::ufIdle){
                fighterModel->changeAnimation("idle");
				fighterModel->setRandomFrame();
                fighterState = _state;
            }
        break;

        case Enumeration::UnitFighterState::ufConfront:
            if(fighterState != Enumeration::UnitFighterState::ufConfront){
                fighterModel->changeAnimation("walk");
				fighterModel->setRandomFrame();
                fighterState = _state;
            }
        break;

        default: 
            std::cout << "INVALID UNITfightER STATE \n";
        break;
    }
}

void UnitFighter::ufAttackState() {
    /* Do nothing */
}

void UnitFighter::ufMoveState() {
    move();
    /* Esto es el bug */
    if(hasArrived()){
        std::cout << "Pues he llegado primo \n";
        switchState(Enumeration::UnitFighterState::ufIdle);
    }
}

void UnitFighter::ufIdleState() {
    /* Do nothing */
    //move();
}

/* Yeah, hit hards the CPU */
void UnitFighter::ufConfrontState() {
    if(inRange()){
        switchState(Enumeration::UnitFighterState::ufAttack);
    }
    else{
        Entity* dummyTarget = unitLeader->getTarget();
        if(dummyTarget != nullptr){
            if(dummyTarget->getEntityType() == Enumeration::EntityType::Building){
                /* Fix this method */
                Vector2<f32> vDirection = dummyTarget->getPosition() - vectorPosition;
                f32 distance = std::sqrt(std::pow(vDirection.x, 2) +
                                         std::pow(vDirection.y, 2));

                vDirection = vDirection / distance;
                vDirection = vDirection * (distance - dummyTarget->getHitbox().getRadius());
                setDestiny(vectorPosition + vDirection);
            } else{
                std::vector< Vector2<f32> > tmp = dummyTarget->getInnerComponentsPosition();
                if(tmp.size() > 0){
                    i32 counter = fighterIndex;
                    if(counter < tmp.size()){
                        setDestiny(tmp[counter]);
                    }
                    else{
                        while(counter >= tmp.size()){
                            counter -= tmp.size();
                        }
                        if(counter >= 0){
                            setDestiny(tmp[counter]);
                        }
                        else{
                            setDestiny(tmp[0]);
                        }
                    }
                }
            }
            move();
        }
    }
}

void UnitFighter::setNearFighters(std::vector<UnitFighter*>& _nearFighters) {
    nearFighters = _nearFighters;
}

void UnitFighter::setActive(bool _active) {
    fighterModel -> setActive(_active);
}

Vector2<f32> UnitFighter::getVectorPosition() const{
    return vectorPosition;
}

Vector2<f32> UnitFighter::getVectorSpeed() const{
    return vectorSpeed;
}

Vector2<f32> UnitFighter::getVectorDestiny() const{
    return vectorDestiny;
}

const f32 UnitFighter::getSpeed() const{
    return speed;
}

bool UnitFighter::hasArrived() {
    if ((vectorPosition - vectorDestiny).dotProduct() < maxDesviation) {
        vectorSpeed = Vector2<f32>(0, 0);
        return true;
    }
    return false;
}

/* Maybe we can calculate it in only one method */
Vector2<f32> UnitFighter::calculateFlocking() {
    Vector2<f32> alignment(0, 0);
    Vector2<f32> cohesion(0, 0);
    Vector2<f32> separation(0, 0);
    Vector2<f32> flock(0, 0);
    i32 k(0);
    f64 distance(0);
    Vector2<f32> other(0, 0);

    for (std::size_t i = 0; i < nearFighters.size(); i++) {
        if (nearFighters[i] != this) {
            other = nearFighters[i]->getVectorPosition();
            distance = std::sqrt(std::pow(other.x - vectorPosition.x, 2) + std::pow(other.y - vectorPosition.y, 2));
            if (distance < 15.0f) {
                /* Alignment */
                alignment += nearFighters[i]->getVectorSpeed();
                /* Cohesion */
                cohesion += other;
                /* Separation */
                separation += (other - vectorPosition);
                /* Count */
                k++;
            }
        }   
    }
    /* Final maths */
    if (k == 0) {
        return flock;
    }

    /* Alignment */
    alignment = alignment / k;
    if (alignment.x != 0 || alignment.y != 0) {
        distance = std::sqrt(std::pow(alignment.x, 2) + std::pow(alignment.y, 2));
        alignment = alignment / distance;
    }

    /* Cohesion */
    cohesion = cohesion / k;
    cohesion = cohesion - vectorPosition;
    if (cohesion.x != 0 || cohesion.y != 0) {
        distance = std::sqrt(std::pow(cohesion.x, 2) + std::pow(cohesion.y, 2));

        cohesion = cohesion / distance;
    }
    
    /* Separation */
    separation = (separation * (-1)) / k;
    if (separation.x != 0 || separation.y != 0) {
        distance = std::sqrt(std::pow(separation.x, 2) + std::pow(separation.y, 2));
        separation = separation / distance;
    }

    flock = alignment * 1.1f + cohesion * 1.0f + separation * 1.1f;

    /* Normalize Flock */
    if (flock.x != 0 || flock.y != 0) {
        distance = std::sqrt(std::pow(flock.x, 2) + std::pow(flock.y, 2));
        flock = flock / distance;
    }

    return flock;
}

/* Change this method, so only is called when set destiny is called */
/* Take flocking out of here */
void UnitFighter::calculateDirection() {
    Vector2<f32> _incVector = vectorDestiny - vectorPosition;
    /* Calculate speed */
    f32 distance = std::sqrt(std::pow(_incVector.x, 2) + std::pow(_incVector.y ,2));
    if (distance != 0) {
        vectorDirection = _incVector / distance;
        vectorDirection += calculateFlocking();

        //fighterModel->setRotation(Vector3<f32>(0, std::atan2(vectorDirection.y, vectorDirection.x)*180.0f/3.1415926f + 90.f, 0));
        rotationAngle = std::atan2(vectorDirection.y, vectorDirection.x) * (180.0f / 3.1415926f) + 90.f;
        std::cout << "Angulo primo: " << rotationAngle << "\n";
        rotationClock->start();
        /* Normalize */
        if (vectorDirection.x != 0 || vectorDirection.y != 0) {
            distance = std::sqrt(std::pow(vectorDirection.x, 2) + std::pow(vectorDirection.y, 2));
            vectorDirection = vectorDirection / distance;   
            
            //fighterModel->setRotation(Vector3<f32>(0, std::atan2(vectorDirection.y, vectorDirection.x)*180.0f/3.1415926f + 90.f, 0));
        }
        else{
            std::cout << "Te pille cabron \n";
        }
    }   
    else{
        std::cout << "Ops \n";
        vectorDirection = Vector2<f32>(0, 0);
    }
}

bool UnitFighter::inRange(){
    bool inRange = false;

    Vector2<f32> tmp(vectorDestiny - vectorPosition);
    f32 distance = std::sqrt(std::pow(tmp.x, 2) + 
                             std::pow(tmp.y, 2));
 
    if( distance <= attackRange){
        inRange = true;
    }
    
    return inRange;
}

void UnitFighter::rotateFighter(){
    if(std::abs(rotationAngle) <= 15.0f){
        fighterModel->setRotation(Vector3<f32>(0, rotationAngle, 0));
        rotationAngle = 0;
        rotationClock->stop();
    }
    else{
        if (rotationAngle > 0.0f){
            fighterModel->setRotation(Vector3<f32>(0, 15, 0));
            rotationAngle -= 15.0f;
        }
        else{
            fighterModel->setRotation(Vector3<f32>(0, -15, 0));
            rotationAngle += 15.0f;
        }
    }
}
