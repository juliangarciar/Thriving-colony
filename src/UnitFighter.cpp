#include "UnitFighter.h"
#include "MathEngine/Vector3.h"
#include "Map.h"
#include "GraphicEngine/Window.h"
#include "IOEngine/Timer.h"

UnitFighter::UnitFighter(SceneNode* _parent, i32 _id, std::string _path, f32 _speed):speed(_speed), maxDesviation(_speed * 0.5f), maxTime(0), unitFighterClock(nullptr){
    fighterModel = new Model(_parent, _id, _path);
    vectorPosition = Vector2<f32>(0, 0);
    vectorSpeed = Vector2<f32>(0, 0);
    vectorDestiny = Vector2<f32>(0, 0);
    vectorDirection = Vector2<f32>(0, 0);
    nearFighters = std::vector< UnitFighter* >();
    unitFighterClock = new Timer(1, false, false);
    unitFighterClock->setCallback([&]{
        isMoving = false;
    });
}
UnitFighter::~UnitFighter(){
    delete unitFighterClock;
    delete fighterModel;
    nearFighters.clear();
}
void UnitFighter::setPosition(Vector2<f32> _pos){
    vectorPosition = _pos;
}
void UnitFighter::setDestiny(Vector2<f32> _dest){
    vectorDestiny = _dest;
    Vector2<f32> vectorDistance = (vectorDestiny - vectorPosition);
    maxTime = (std::sqrt(std::pow(vectorDistance.x, 2) + std::pow(vectorDistance.y, 2))) / speed * 0.016f ;
    maxTime += 0.1f * maxTime;
    unitFighterClock->changeDuration(maxTime);
    unitFighterClock->restart();

    isMoving = true;
}
void UnitFighter::move(){
    if(!hasArrived()){
        calculateDirection();
        Vector2<f32> _oldPosition = vectorPosition;
        vectorSpeed = vectorDirection * speed;
        vectorPosition += vectorSpeed;
        vectorPosition = _oldPosition + (vectorPosition - _oldPosition) * Window::Instance()->getDeltaTimeVariance();
        fighterModel->setPosition(Vector3<f32>(vectorPosition.x, Map::Instance()->getTerrain()->getY(vectorPosition.x, vectorPosition.y), vectorPosition.y));
    }   
    else{
        isMoving = false;
        unitFighterClock->stop();
    }
}
/* Check this method */
void UnitFighter::update(){
    if(isMoving){
        //nearFighters = _nearFighters;
        move();
    }
}

void UnitFighter::setNearFighters(std::vector<UnitFighter*>& _nearFighters){
    nearFighters = _nearFighters;
}

void UnitFighter::setActive(bool _active){
    fighterModel->setActive(_active);
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
bool UnitFighter::hasArrived(){
    if((vectorPosition - vectorDestiny).dotProduct() < maxDesviation){
        vectorSpeed = Vector2<f32>(0, 0);
        return true;
    }
    return false;
}
/* Maybe we can calculate it in only one method */
Vector2<f32> UnitFighter::calculateFlocking(){
    Vector2<f32> alignment(0, 0);
    Vector2<f32> cohesion(0, 0);
    Vector2<f32> separation(0, 0);
    Vector2<f32> flock(0, 0);
    i32 k(0);
    double distance(0);
    Vector2<f32> other(0, 0);

    for(std::size_t i = 0; i < nearFighters.size(); i++){
        if(nearFighters[i] != this){
            other = nearFighters[i]->getVectorPosition();
            distance = std::sqrt(std::pow(other.x - vectorPosition.x, 2) + 
                                 std::pow(other.y - vectorPosition.y, 2));

            if(distance < 15.0f){
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
    if(k == 0){
        return flock;
    }

    /* Alignment */
    alignment = alignment / k;

    if(alignment.x != 0 || alignment.y != 0){
        distance = std::sqrt(std::pow(alignment.x, 2) + 
                             std::pow(alignment.y, 2));

        alignment = alignment / distance;
    }

    /* Cohesion */
    cohesion = cohesion / k;
    cohesion = cohesion - vectorPosition;

    if(cohesion.x != 0 || cohesion.y != 0){
        distance = std::sqrt(std::pow(cohesion.x, 2) +
                             std::pow(cohesion.y, 2));

        cohesion = cohesion / distance;
    }
    
    
    /* Separation */
    separation = (separation * (-1)) / k;

    if(separation.x != 0 || separation.y != 0){
        distance = std::sqrt(std::pow(separation.x, 2) +
                            std::pow(separation.y, 2));
    
        separation = separation / distance;
    }
    

    flock = alignment * 1.1f + cohesion * 1.0f + separation * 1.1f;

    /* Normalize Flock */
    if(flock.x != 0 || flock.y != 0){
        distance = std::sqrt(std::pow(flock.x, 2) + 
                             std::pow(flock.y, 2));
    
        flock = flock / distance;
    }
    

    return flock;
}
void UnitFighter::calculateDirection(){
    Vector2<f32> _incVector = vectorDestiny - vectorPosition;
    /* Calculate speed */
    f32 distance = std::sqrt(std::pow(_incVector.x, 2) + 
                             std::pow(_incVector.y ,2));
    
    if(distance != 0){
        vectorDirection = _incVector / distance;
        vectorDirection += calculateFlocking();
        
        /* Normalize */
        if(vectorDirection.x != 0 || vectorDirection.y != 0){
            distance = std::sqrt(std::pow(vectorDirection.x, 2) + 
                             std::pow(vectorDirection.y, 2));

            vectorDirection = vectorDirection / distance;   
        }
    }   
    else{
        vectorDirection = Vector2<f32>(0, 0);
    }
}