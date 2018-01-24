#ifndef STATE_H
#define STATE_H

class State {
    public:
        virtual void Init() = 0;
        virtual void Input() = 0;
        virtual void Update() = 0;
        virtual void Render() = 0;
        virtual void CleanUp() = 0;
};

#endif

