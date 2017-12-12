#include "Ranged.h"

Ranged::Ranged(irr::core::vector3df *vectorData) : Unit(vectorData)
{
Ranged::Ranged(int hitPoints, Vector3<float>* pos, int _moveSpeed, int _attackSpeed, int _damage, int _attackRadius, int _viewRadius, bool _team, Box3D<float>* hitboxPnt, Model* modelPnt) : Unit(hitPoints, pos, _moveSpeed, _attackSpeed, _damage, _attackRadius, _viewRadius, _team, hitboxPnt, modelPnt) {

}

Ranged::~Ranged() {

}