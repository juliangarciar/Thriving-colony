#include "ServiceNode.h"
#include "SchoolNode.h"
#include "HospitalNode.h"
#include "MarketNode.h"

ServiceNode::ServiceNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = new Node*[3];
    children[0] = new SchoolNode(this);
    children[1] = new HospitalNode(this);
    children[2] = new MarketNode(this);
}

ServiceNode::~ServiceNode(){
    delete father;
    delete[] children;
}

void ServiceNode::question() {
    //std::cout << Voy a invertir en servicios << std::endl;
    float cityLvl = IA::getInstance() -> getHappiness();
    if (cityLvl >= tree -> getHospitalMilestone()) {
        children[0] -> question();
    } else {
        if (cityLvl >= tree -> getMarketMilestone()) {
            children[1] -> question();
        } else {
            children[2] -> question();
        }
    }
}