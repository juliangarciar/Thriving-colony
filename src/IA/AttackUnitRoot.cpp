#include "AttackUnitRoot.h"
#include "UnitAttackNode.h"
#include "BuildingAttackNode.h"

AttackUnitRoot::AttackUnitRoot() : Node() {
    father = 0;
    children = new Node*[2];
    children[0] = new UnitAttackNode(this);
    children[1] = new BuildingAttackNode(this);
}

AttackUnitRoot::~AttackUnitRoot(){
    delete father;
}

void AttackUnitRoot::question() {

}