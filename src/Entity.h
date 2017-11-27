#ifndef ENTITY_H
#define ENTITY_H

class Entity {

    public:
        Entity(int);
        virtual ~Entity();

        int getHP();
        void takeDamage(int);
        void die();

    protected:
        int hpMax;
        int hp;
    private:
};

#endif