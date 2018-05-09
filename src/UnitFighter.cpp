#include "UnitFighter.h"

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
//void UnitFighter::setSpeed(f32 _spd){
//    speed = _spd;
//}
void UnitFighter::move(){
    if(!hasArrived()){
        /* Move */
        calculateDirection();
        /* Add flocking */
        vectorSpeed = speed * vectorDirection;
        vectorPosition += vectorSpeed;
        fighterModel->setPosition(vectorPosition);
    }
    else{
        isMoving = false;
    }
}
void UnitFighter::update(std::vector<UnitFighter*> &_nearFighters){
    if(isMoving){
        move();
    }
}
//void UnitFighter::setNearFighters(std::vector<UnitFighter*> &_nearFighters){
//    
//}
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
//f32 UnitFighter::getSpeed() const{
//    f32 tmp(speed);
//    return tmp;
//}
bool UnitFighter::hasArrived(){
    if((vectorPosition - vectorDestiny).dotProduct < 1.0){
        vectorSpeed = Vector2<f32>(0, 0);
        vectorDirection = Vector2<f32>(0, 0);
        //vectorDestiny = Vector2<f32>(0, 0);
        return true;
    }
    return false;
}
/* Maybe we can calculate it in only one method */
Vector2<f32> UnitFighter::calculateFlocking(){
    Vector2<f32> _flock;
    return _flock;
}
Vector2<f32> UnitFighter::calculateDirection(){
    
    f32 incX = vectorDestiny.x - vectorPosition.x;
    f32 incY = vectorDestiny.y - vectorPosition.y;
    /* Calculate speed */
    f32 distance = std::sqrt(std::pow(incX, 2) + 
                            std::pow(incY ,2));
    
    vectorDirection = Vector2<f32>(incX / distance, incY / distance);

    return dummy;
}