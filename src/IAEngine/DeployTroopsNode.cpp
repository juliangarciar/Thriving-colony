#include "DeployTroopsNode.h"

#include <IA.h>
#include <IOEngine/IO.h>

DeployTroopsNode::DeployTroopsNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

DeployTroopsNode::~DeployTroopsNode() {
    delete father;
}

void DeployTroopsNode::question() {
    IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::DeployingTroops);
    //std::cout<<"Despliego tropas"<<std::endl;
    IO::Instance() -> getEventManager() -> triggerEvent(Enumeration::DeployTroopsIA);
}