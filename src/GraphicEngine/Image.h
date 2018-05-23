#ifndef IMAGE_H
#define IMAGE_H

#include <OBDEngine/OBDImage.h>

#include <Types.h>
#include <MathEngine/Vector3.h>
#include <MathEngine/Color.h>

class Image {
    public:
        Image(std::string, glm::vec3);
        ~Image();

		void setPosition(Vector3<f32> position);
		void setActive(bool);
    private:
		OBDImage *i;
};

#endif