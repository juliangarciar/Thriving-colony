#ifndef ENTITY_H
#define ENTITY_H

#include "GraphicEngine/Vector3.h"
#include "GraphicEngine/Box3D.h"
#include "GraphicEngine/Model.h"

class Entity {

    public:
        Entity(int, Vector3<float>*, bool, Box3D<float>*, Model*);
        virtual ~Entity();

        int getHP();
        void takeDamage(int);
        void die();

        Vector3<float>* getPosition();

        Box3D<float>* getHitbox();
        Model* getModel();

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

        Box3D<float>* hitbox;
        Model* model;

    private:
};

#endif