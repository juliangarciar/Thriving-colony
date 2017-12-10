#include "Ranged.h"

Ranged::Ranged(int hitPoints, Vector3<float>* pos, int _moveSpeed, int _attackSpeed, int _damage, int _attackRadius, int _viewRadius) : Unit(hitPoints, pos, _moveSpeed, _attackSpeed, _damage, _attackRadius, _viewRadius) {

}

Ranged::~Ranged() {

}