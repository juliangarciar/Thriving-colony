#ifndef ENTITY_H
#define ENTITY_H

class Entity {

    public:
        Entity(int, int);
        virtual ~Entity();

        int getHP();
        void takeDamage(int);
        void attack();
        void die();

    protected:
        int hpMax;
        int hp;  
        int attackDamage;
        Entity* target;
    private:
};

#endif