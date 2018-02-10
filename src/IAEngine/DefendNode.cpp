#include "DefendNode.h"
#include "DeployTroopsNode.h"
#include "MeleeFootmenNode.h"
#include "BarrackNode.h"
#include "../IA.h"

DefendNode::DefendNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = new Node*[4];
    //children[0] = new CloseDoorsNode(this); //ToDo: puerta
    children[1] = new DeployTroopsNode(this);
    children[2] = new MeleeFootmenNode(this);
    children[3] = new BarrackNode(this);
}

DefendNode::~DefendNode() {
    delete father;
    delete[] children;
}

void DefendNode::question() {
    //ToDo: defend
    if (/*IA::Instance() -> getClosedDoors()*/false == false) { //ToDo: puerta
        children[0] -> question();
    } else {
        if (IA::Instance() -> getUnitManager() -> areTroopsDeployed() == false) {
            children[1] -> question();
        } else {
            if (IA::Instance() -> getBuildingManager() -> getAmount(Enumeration::BuildingType::Barrack) > 0) {
                children[2] -> question();
            } else {
                children[3] -> question();
            }
        }
    }
}