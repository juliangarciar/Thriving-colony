#include "MeleeFootmenNode.h"
#include "BarrackNode.h"
#include "../IA.h"

MeleeFootmenNode::MeleeFootmenNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;/*
    children = new Node*[1];
    children[0] = new BarrackNode(this);*/
}

MeleeFootmenNode::~MeleeFootmenNode(){
    delete father;
    //delete[] children;
}

void MeleeFootmenNode::question() {

    IA::getInstance() -> setChoiceIndex(Enumeration::IAChoices::TrainMeleeFootman);
    if (IA::getInstance() -> getBarrackBuilt()) {
        //std::cout << "Genero un soldado a pie melee" << std::endl;
        //Esto va en el constructor
        if (IA::getInstance() -> getUnitManager() -> isSolvent(Enumeration::UnitCost::MeleeFootmenMetalCost, Enumeration::UnitCost::MeleeFootmenCrystalCost, Enumeration::Team::IA)) {
            // Unit type
            Enumeration::UnitType unitData = Enumeration::UnitType::StandardM;
            IA::getInstance() -> getUnitManager() -> createTroop(unitData);
        }
    } else {
        IA::getInstance() -> getTree() -> setRequireBarrack(true);
        //children[0] -> question();
    }
}