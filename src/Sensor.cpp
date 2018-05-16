#include "Sensor.h"
#include "Unit.h"
#include <WorldEngine/WorldGeometry.h>

Sensor::Sensor(Entity* _entity, i32 maxRadius):propietary(_entity),
                                               sensorHitbox(Vector2<f32>(0,0),
                                                            Vector2<f32>(std::sqrt(std::pow(maxRadius,2) + std::pow(maxRadius,2)),
                                                                         std::sqrt(std::pow(maxRadius,2) + std::pow(maxRadius,2))))
{}

Sensor::~Sensor(){

}

void Sensor::update(){
    detectedEntities.clear();
    detectedFloking.clear();
    WorldGeometry::Instance()->getCollidingEntities(sensorHitbox, detectedEntities, detectedFloking);
}

void Sensor::move(Vector2<f32> _vectorPosition){
    sensorHitbox.moveHitbox(_vectorPosition);
}