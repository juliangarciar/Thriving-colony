#ifndef SENSOR_H
#define SENSOR_H
#include <MathEngine/Box2D.h>
#include <MathEngine/Vector2.h>
#include <vector>

class Entity;
class Sensor{
    public:
        Sensor(Entity* _entity);
        ~Sensor();
        void update();
        void move(Vector2<f32> _vectorPosition);
    private:
        Entity* propietary;
        Entity* priorityTarget;
        Box2D sensorHitbox;
};
#endif