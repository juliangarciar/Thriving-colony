#ifndef ENTITY_H
#define ENTITY_H

#include "GraphicEngine/Vector3.h"
#include "Player.h"

class Entity {

    public:
        Entity(int, Vector3<float>, Player*);
        virtual ~Entity();

        int getHP();
        void takeDamage(int);
        void die();

        Vector3<float>* getPosition();

    protected:
        Vector3<float>* position;

        int hpMax;
        int hp;

        Player* team;
    private:
};

#endif