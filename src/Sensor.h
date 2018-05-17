#ifndef SENSOR_H
#define SENSOR_H
#include <MathEngine/Box2D.h>
#include <MathEngine/Vector2.h>
#include <vector>

class Entity;
class Unit;
class Sensor{
    public:
        Sensor(Unit* _entity, i32 maxRadius);
        ~Sensor();
        void update();
        void move(Vector2<f32> _vectorPosition);
    private:
        Unit* propietary;
        Box2D sensorHitbox;
        std::vector< Unit* > detectedFloking;
        std::vector< Entity* > detectedEntities;
};
#endif