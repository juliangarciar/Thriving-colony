#include "Sensor.h"
#include "Unit.h"
#include <WorldEngine/WorldGeometry.h>

Sensor::Sensor(Unit* _entity, i32 maxRadius):propietary(_entity),
                                               sensorHitbox(Vector2<f32>(0,0),
                                                            Vector2<f32>(std::sqrt(std::pow(maxRadius,2) + std::pow(maxRadius,2)),
                                                                         std::sqrt(std::pow(maxRadius,2) + std::pow(maxRadius,2))))
{}

Sensor::~Sensor(){

}

void Sensor::update(){
    detectedEntities.clear();
    detectedEntities.resize(0);
    detectedFloking.clear();
    detectedFloking.resize(0);
    WorldGeometry::Instance()->getCollidingEntities(sensorHitbox, detectedEntities, detectedFloking);
    propietary->updateFlockingSensor(detectedFloking);
    //std::cout << "Entidades cercanas: " << detectedEntities.size() << ". Flocking: " << detectedFloking.size() << "\n";
}

void Sensor::move(Vector2<f32> _vectorPosition){
    sensorHitbox.moveHitbox(_vectorPosition);
}