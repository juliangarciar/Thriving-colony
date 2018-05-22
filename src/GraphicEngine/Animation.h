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

#include <IOEngine/Timer.h>

class Animation {
    public:
        Animation(SceneNode *parent, std::string animationJSON);

        ~Animation();

		void changeAnimation(std::string animationName);

		static void preloadAnimation(std::string);

        void setActive(bool a);
		void setColor(Color);

        void setPosition(Vector3<f32> pos);
        void setRotation(Vector3<f32> r);
        void setScale(Vector3<f32> s);

		void setRandomFrame();

		Timer *getAnimationTimer();
    private:
		SceneNode *animationLayer;
        std::map<std::string, f32> *animationDelays;
        std::map<std::string, OBDAnimation*> *animations;
        
        
		Timer *frameTimer;

		OBDAnimation *currentAnimation;
};

#endif