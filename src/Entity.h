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
<<<<<<< HEAD
=======

>>>>>>> 91a70b0e5847464075abdf55097852f854b89175
    private:
};

#endif