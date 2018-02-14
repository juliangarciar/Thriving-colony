#include "UnitNode.h"
#include "MeleeNode.h"
#include "RangeNode.h"
#include "SiegeNode.h"
#include <IA.h>

UnitNode::UnitNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = new Node*[3];
    children[0] = new MeleeNode(this);
    children[1] = new RangeNode(this);
    children[2] = new SiegeNode(this);
}

UnitNode::~UnitNode() {
    delete father;
    delete[] children;
}

void UnitNode::question() {
    //First subsubbranch: Melee
    if (IA::Instance() -> getTree() -> calculateMeleeRate() < IA::Instance() -> getTree() -> getMeleeThreshold()) {
        //std::cout << "Voy a hacer melees" << std::endl;
        children[0] -> question();
    } else {
        //Second subsubbranch: Range
        if (IA::Instance() -> getTree() -> calculateRangeRate() < IA::Instance() -> getTree()  -> getRangeThreshold()) {
            //std::cout << "Voy a hacer rangos" << std::endl;
            children[1] -> question();
        } else {
            //Third subsubbranch: Siege
            //std::cout << "Voy a hacer asedio" << std::endl;
            children[2] -> question();
        }
    }
}