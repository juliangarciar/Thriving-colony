#ifndef ENTITY_H
#define ENTITY_H

#include "GraphicEngine/Vector3.h"
#include "GraphicEngine/Box3D.h"
#include "GraphicEngine/Model.h"
#include "Enumeration.h"


class Entity {

    public:
        //The consctructor is empty because the object it's constructed in the child
        Entity();
        virtual ~Entity();

        int getHP();
        void takeDamage(int);
        void die();

        Vector3<float> *getPosition();
        Box3D<float> *getHitbox();
        Model *getModel();

    protected:
        Vector3<float>* position;
        int hpMax;
        int hp;
        int happiness;

        /*
        * Indicates the propetary of the entity
        * False -> IA
        * True -> Human
        */
        bool team;

        Box3D<float>* hitbox;
        Model* model;

    private:
};

#endif