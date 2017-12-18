#ifndef BOX_3D_H
#define BOX_3D_H

#include <iostream>
#include <irrlicht.h>

using namespace irr;

template <class T>
class Box3D {
	public:
		Box3D();
		Box3D(core::aabbox3d<T> box);

		~Box3D();

		void setPosition(core::aabbox3d<T> box);

		bool intersects(Box3D<T> other);

		core::aabbox3d<T> getAABBox3D();
	private:
		core::aabbox3d<T> box;
};

#endif