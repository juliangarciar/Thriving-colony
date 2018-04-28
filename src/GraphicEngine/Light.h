#ifndef LIGHT_H
#define LIGHT_H

#include <OBDEngine/OBDLight.h>

#include <Types.h>
#include <MathEngine/Vector3.h>

class Light {
    public:
        Light(Vector3<f32> position, f32 intensity);
        ~Light();

		void setPosition(Vector3<f32> position);
    private:
		OBDLight *l;
};

#endif