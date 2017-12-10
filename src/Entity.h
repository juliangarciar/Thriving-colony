#ifndef ENTITY_H
#define ENTITY_H

#include "GraphicEngine/Vector3.h"

class Entity {

    public:
        Entity(int);
        virtual ~Entity();

        int getHP();
        void takeDamage(int);
        void die();

        Vector3 getPosition();

    protected:
        Vector3 *position;
        int hpMax;
        int hp;

    private:
};

#endif