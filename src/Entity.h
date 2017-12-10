#ifndef ENTITY_H
#define ENTITY_H

#include "GraphicEngine/Vector3.h"

class Entity {

    public:
        Entity(int, Vector3<float>*, bool);
        virtual ~Entity();

        int getHP();
        void takeDamage(int);
        void die();

        Vector3<float>* getPosition();

    protected:
        Vector3<float>* position;

        int hpMax;
        int hp;

        /*
        * Indicates the propetary of the entity
        * False -> IA
        * True -> Human
        */
        bool team; 

    private:
};

#endif