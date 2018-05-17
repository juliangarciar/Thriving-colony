#ifndef ANIMATION_H
#define ANIMATION_H

#include <irrlicht/irrlicht.h>
#include <Types.h>
#include <map>
#include <vector>
#include <GraphicEngine/SceneNode.h>
#include <GraphicEngine/Material.h>
#include <MathEngine/Color.h>
using namespace irr;

class Animation {
    public:
        Animation(SceneNode *parent, i32 id, std::map< std::string, std::vector<std::string>> *paths);

        ~Animation();

        void setActive(bool a);
        void setMaterial(Material *m);
        void setPosition(Vector3<f32> pos);
        void setScale(Vector3<f32> s);
        void rotate(f32 x, f32 y);
        void setID(i32 id);
        i32 getID();
        Vector3<f32> getPosition();
        scene::IMeshSceneNode *getModel();
		void setMaterialColor(Color);

        void update();
        void setFrames(i32 i, i32 f);
        void setClip(i32);
        
        
    private:
        std::map< std::string, std::vector<scene::IMeshSceneNode*>*> *frames;
        scene::ITriangleSelector *selector = 0;

        i32 currentFrame;
        i32 currentClip;

        i32 startingFrame;
        i32 finalFrame;

        i32 ID;
};

#endif