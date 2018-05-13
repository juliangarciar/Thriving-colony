#include "UnitFighter.h"
#include "MathEngine/Vector3.h"
#include "Map.h"

UnitFighter::UnitFighter(SceneNode* _parent, i32 _id, std::string _path, f32 _speed):speed(_speed){
    fighterModel = new Model(_parent, _id, _path);
    vectorPosition = Vector2<f32>(0, 0);
    vectorSpeed = Vector2<f32>(0, 0);
    vectorDestiny = Vector2<f32>(0, 0);
    vectorDirection = Vector2<f32>(0, 0);
    nearFighters = std::vector< UnitFighter* >();
}
UnitFighter::~UnitFighter(){
    delete fighterModel;
    nearFighters.clear();
}
void UnitFighter::setPosition(Vector2<f32> _pos){
    vectorPosition = _pos;
}
void UnitFighter::setDestiny(Vector2<f32> _dest){
    vectorDestiny = _dest;
    isMoving = true;
}
void UnitFighter::move(){
    if(!hasArrived()){
        calculateDirection();
        /* Add flocking */
        vectorSpeed = vectorDirection * (speed / 100.0f);
        vectorPosition += vectorSpeed;
        fighterModel->setPosition(Vector3<f32>(vectorPosition.x, Map::Instance()->getTerrain()->getY(vectorPosition.x, vectorPosition.y), vectorPosition.y));
    }
    else{
        isMoving = false;
    }
}
void UnitFighter::update(std::vector<UnitFighter*> &_nearFighters){
    if(isMoving){
        //std::cout << "Im a fighter and im movin \n";
        nearFighters = _nearFighters;
        //std::cout << "Unitfighters count: " << nearFighters.size() << "\n";
        move();
    }
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
    if((vectorPosition - vectorDestiny).dotProduct() < 1.0f){
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
    f64 distance(0);
    Vector2<f32> other(0, 0);
    for(std::size_t i = 0; i < nearFighters.size(); i++){
        if(nearFighters[i] != this){
            other = nearFighters[i]->getVectorPosition();
            distance = std::sqrt(std::pow(other.x - vectorPosition.x, 2) + 
                                 std::pow(other.y - vectorPosition.y, 2));

            //std::cout << distance << "\n";
            if(distance < 20.0f){
                //std::cout << "Ops \n";
                /* Alignment */
                alignment += nearFighters[i]->getVectorSpeed();
                /* Cohesion */
                cohesion += other;
                /* Separation */
                separation += other - vectorPosition;
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
    distance = std::sqrt(std::pow(alignment.x, 2) + 
                         std::pow(alignment.y, 2));

    if(alignment.x != 0 && alignment.y != 0){
        alignment = alignment / distance;
    }

    /* Cohesion */
    cohesion = cohesion / k;
    cohesion = cohesion - vectorPosition;
    distance = std::sqrt(std::pow(cohesion.x, 2) +
                         std::pow(cohesion.y, 2));

    cohesion = cohesion / distance;
    
    /* Separation */
    separation = (separation * (-1)) / k;
    distance = std::sqrt(std::pow(separation.x, 2) +
                         std::pow(separation.y, 2));
    
    separation = separation / distance;

    flock = alignment * 1.1f + cohesion * 0.7f + separation * 1.2f;

    //std::cout << "Flocking " << flock.x << " , " << flock.y << "\n";

    /* Normalize */

    return flock;
}
void UnitFighter::calculateDirection(){
    Vector2<f32> flocking = calculateFlocking();

    f32 incX = vectorDestiny.x - vectorPosition.x;
    f32 incY = vectorDestiny.y - vectorPosition.y;
    /* Calculate speed */
    f32 distance = std::sqrt(std::pow(incX, 2) + 
                             std::pow(incY ,2));
    
    vectorDirection = Vector2<f32>(incX / distance, incY / distance);

    distance = std::sqrt(std::pow(flocking.x, 2) + 
                         std::pow(flocking.y, 2));

    if(distance != 0){
        flocking = flocking / distance;
        vectorDirection += flocking;
        distance = std::sqrt(std::pow(vectorDirection.x, 2) + 
                             std::pow(vectorDirection.y, 2));
        vectorDirection = vectorDirection / distance;    
    }   
}