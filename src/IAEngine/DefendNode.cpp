#include "DefendNode.h"
#include "CloseDoorsNode.h"
#include "DeployTroopsNode.h"
#include "MeleeFootmenNode.h"
#include "BarrackNode.h"
#include "../IA.h"

DefendNode::DefendNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = new Node*[4];
    children[0] = new CloseDoorsNode(this);
    children[1] = new DeployTroopsNode(this);
    children[2] = new MeleeFootmenNode(this);
    children[3] = new BarrackNode(this);
}

DefendNode::~DefendNode(){
    delete father;
    delete[] children;
}

void DefendNode::question() {
    std::cout << "Me atacan" << std::endl;
    //To Do:defend
    if (IA::getInstance() -> getClosedDoors()) {
        children[0] -> question();
    } else {
        if (IA::getInstance() -> getDeployedTroops()) {
            children[1] -> question();
        } else {
            if (IA::getInstance() -> getBarrackBuilt()) {
                children[2] -> question();
            } else {
                children[3] -> question();
            }
        }
    }
}