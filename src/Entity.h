#ifndef ENTITY_H
#define ENTITY_H

#include "GraphicEngine/Vector3.h"
#include "GraphicEngine/Box3D.h"
#include "GraphicEngine/Model.h"
#include "GraphicEngine/SceneNode.h"
#include "GraphicEngine/Window.h"
#include "Enumeration.h"


class Entity {

    public:
        //The consctructor is empty because the object it's constructed in the child
        Entity(int id);
        virtual ~Entity();

        int getHP();
        void takeDamage(int);
        void die();

        void setPosition(Vector3<float> vectorData);

        Vector3<float> *getPosition();
        Box3D<float> *getHitbox();
        Model *getModel();

    protected:
        //SceneNode *modelLayer;
        Model* model;
        Vector3<float> *position;
        Box3D<float>* hitbox;

        int ID;

        int hpMax;
        int hp;
        int happiness;

        /*
        * Indicates the propetary of the entity
        * False -> IA
        * True -> Human
        */
        bool team;

      private:
};

#endif