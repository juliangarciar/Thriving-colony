#include "MeleeFootmenNode.h"
#include "BarrackNode.h"
#include <IA.h>

MeleeFootmenNode::MeleeFootmenNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;/*
    children = new Node*[1];
    children[0] = new BarrackNode(this);*/
}

MeleeFootmenNode::~MeleeFootmenNode() {
    delete father;
    //delete[] children;
}

void MeleeFootmenNode::question() {
    IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::TrainMeleeFootman);
    if (IA::Instance() -> getBuildingManager() -> getAmount("Barrack") > 0) {
        //std::cout << "Genero un soldado a pie melee" << std::endl;
        //Esto va en el constructor
        if (IA::Instance() -> getUnitManager() -> checkCanPay("StandardM")) {
            // Unit type
            IA::Instance() -> getUnitManager() -> createTroop("StandardM");
        }
    } else {
        IA::Instance() -> getTree() -> setRequireBarrack(true);
        //children[0] -> question();
    }
}