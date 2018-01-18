#ifndef STATE_H
#define STATE_H

class State{
    public:
        virtual void init() = 0;
        virtual void input() = 0;
        virtual void update() = 0;
        virtual void render() = 0;
        virtual void cleanUp() = 0;
};

#endif

