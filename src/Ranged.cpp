#include "Ranged.h"

Ranged::Ranged(int hitPoints, Vector3<float>* pos, int _moveSpeed, int _attackSpeed, int _damage, int _attackRadius, int _viewRadius, bool _team) : Unit(hitPoints, pos, _moveSpeed, _attackSpeed, _damage, _attackRadius, _viewRadius, _team) {

}

Ranged::~Ranged() {

}