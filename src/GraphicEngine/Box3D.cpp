#include "Box3D.h"

using namespace irr;

template <class T>
Box3D<T>::Box3D(){

}

template <class T>
Box3D<T>::Box3D(core::aabbox3d<T> box){
	this->box = box;
}

template <class T>
Box3D<T>::~Box3D(){

}

template <class T>
bool Box3D<T>::intersects(Box3D<T> other){
	return box.intersectsWithBox(other.getAABBox3D());
}

template <class T>
core::aabbox3d<T> Box3D<T>::getAABBox3D(){
	return box;
}

template class Box3D<int>;
template class Box3D<float>;