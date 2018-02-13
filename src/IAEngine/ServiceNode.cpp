#include "ServiceNode.h"
#include "SchoolNode.h"
#include "HospitalNode.h"
#include "MarketNode.h"
#include <IA.h>

ServiceNode::ServiceNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = new Node*[3];
    children[0] = new SchoolNode(this);
    children[1] = new MarketNode(this);
    children[2] = new HospitalNode(this);
}

ServiceNode::~ServiceNode() {
    delete father;
    delete[] children;
}

void ServiceNode::question() {
    //std::cout << "Voy a invertir en servicios" << std::endl;
    f32 cityLvl = IA::Instance() -> getCityLevel();
    //std::cout << cityLvl << std::endl;
    if (cityLvl >= IA::Instance() -> getTree() -> getHospitalMilestone()) {
        children[2] -> question();
    } else {
        if (cityLvl >= IA::Instance() -> getTree() -> getMarketMilestone()) {
            children[1] -> question();
        } else {
            children[0] -> question();
        }
    }
}