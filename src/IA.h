#ifndef IA_H
#define IA_H

#include "Player.h"
#include "IA/BehaviourTree.h"

class IA : public Player {
    
    public:
        IA();
        virtual ~IA();
        static IA* getInstance();

        BehaviourTree* getTree();
        
    private:
        static IA* instance;
        BehaviourTree* tree;
};

#endif