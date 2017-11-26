#ifndef ENTITY_H
#define ENTITY_H

class Entity {

    public:
        Entity(int);
        virtual ~Entity();

        int getHP();
        void decreaseHP(int);

    protected:
        int hp;  

    private:
};

#endif