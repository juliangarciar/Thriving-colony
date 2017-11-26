#include "BuildingNode.h"
#include "BarrackNode.h"
#include "BarnNode.h"
#include "WorkshopNode.h"
#include "WallNode.h"
#include "TowerNode.h"

BuildingNode::BuildingNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = new Node*[5];
    children[0] = new BarrackNode(this);
    children[1] = new BarnNode(this);
    children[2] = new WorkshopNode(this);
    children[3] = new WallNode(this);
    children[4] = new TowerNode(this);
}

BuildingNode::~BuildingNode(){
    delete father;
    delete[] children;
}

void BuildingNode::question() {
    if (tree -> getNeedBarracks()) {
        children[0] -> question();
    } else {
        if (tree -> getNeedBarn()) {
            children[1] -> question();
        } else {
            if (tree -> getNeedWorkshop()) {
                children[2] -> question();
            } else {
                if (tree -> getNeedWall()) {
                    children[3] -> question();
                } else {
                    if (tree -> getNeedTower()) {
                        children[4] -> question();
                    }
                }
            }
        }
    }
}