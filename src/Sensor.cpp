#include "Sensor.h"
#include "Unit.h"
#include <WorldEngine/WorldGeometry.h>
#include <Enumeration.h>

Sensor::Sensor(Unit* _entity, i32 maxRadius):propietary(_entity),
                                               sensorHitbox(Vector2<f32>(0,0),
                                                            Vector2<f32>(std::sqrt(std::pow(maxRadius,2) + std::pow(maxRadius,2)),
                                                                         std::sqrt(std::pow(maxRadius,2) + std::pow(maxRadius,2))))
{}

Sensor::~Sensor(){

}

void Sensor::update(){
    detectedEnemyEntities.clear();
    detectedEnemyEntities.resize(0);
    WorldGeometry::Instance()->getCollidingEntities(sensorHitbox, detectedEnemyEntities, propietary->getTeam());
    //propietary->updateFlockingSensor(detectedFloking);
    std::cout << "Entidades cercanas: " << detectedEnemyEntities.size() << "\n";
}

void Sensor::move(Vector2<f32> _vectorPosition){
    sensorHitbox.moveHitbox(_vectorPosition);
}