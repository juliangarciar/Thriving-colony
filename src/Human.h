#ifndef HUMAN_H
#define HUMAN_H

#include "Player.h"
#include "IA/BehaviourTree.h"

class Human : public Player {
    
    public:
        Human();
        virtual ~Human();
        static Human* getInstance();

        BehaviourTree* getTree();
        
    private:
        
        static Human* instance;
        BehaviourTree* tree;
};

#endif