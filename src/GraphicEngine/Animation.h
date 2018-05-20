#ifndef ANIMATION_H
#define ANIMATION_H

#include <Types.h>
#include <map>
#include <vector>
#include <cmath>

#include <OBDEngine/OBDAnimation.h>
#include <OBDEngine/ResourceManager/ResourceJSON.h>

#include <GraphicEngine/SceneNode.h>
#include <GraphicEngine/Material.h>

#include <MathEngine/Color.h>

class Animation {
    public:
        Animation(SceneNode *parent, std::string animationJSON);

        ~Animation();

        void update();

		void changeAnimation(std::string animationName);

        void setActive(bool a);
		void setColor(Color);

        void setPosition(Vector3<f32> pos);
        void setRotation(Vector3<f32> r);
        void setScale(Vector3<f32> s);
    private:
		SceneNode *animationLayer;
        std::map<std::string, OBDAnimation*> *animations;

		OBDAnimation *currentAnimation;
};

#endif