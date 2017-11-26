#include "BuildingAttackNode.h"
#include "MainBuildingAttackNode.h"
#include "TowerAttackNode.h"
#include "DamagedBuildingNode.h"
#include "CloseBuildingNode.h"
#include "DamagedWallNode.h"
#include "WallAttackNode.h"

BuildingAttackNode::BuildingAttackNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = new Node*[6];
    children[0] = new MainBuildingAttackNode(this);
    children[1] = new TowerAttackNode(this);
    children[2] = new DamagedBuildingNode(this);
    children[3] = new CloseBuildingNode(this);
    children[4] = new DamagedWallNode(this);
    children[5] = new WallAttackNode(this);
}

BuildingAttackNode::~BuildingAttackNode(){

}