#include "MountedMeleeNode.h"
#include "BarnNode.h"
#include <IA.h>

MountedMeleeNode::MountedMeleeNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
    /*
    children =  new Node*[1];
    children[0] = new BarnNode(this);
    */
}

MountedMeleeNode::~MountedMeleeNode() {
    delete father;
    //delete[] children;
}

void MountedMeleeNode::question() {
    IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::TrainMountedMelee);
    if (IA::Instance() -> getBuildingManager() -> getAmount("Barn") > 0) {
    //std::cout << "Genero un soldado montado melee" << std::endl;
        if (IA::Instance() -> getUnitManager() -> checkCanPay("AdvancedM")) {
            // Unit type
            IA::Instance() -> getUnitManager() -> createTroop("AdvancedM");
        }
    } else {
        IA::Instance() -> getTree() -> setRequireBarn(true);
        //children[0] -> question();
    }
}