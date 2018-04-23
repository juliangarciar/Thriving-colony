#ifndef BILLBOARD_H
#define BILLBOARD_H
#include <irrlicht/irrlicht.h>
#include <Types.h>
#include <MathEngine/Vector3.h>
#include "SceneNode.h"
#include "Window.h"
using namespace irr;

class Billboard {
    
    public:
        Billboard(SceneNode* parent, i32 id, Vector3<f32> pos);
        ~Billboard();

        void setColor(video::SColor top, video::SColor bot);
        void setSize(f32 w, f32 h);

        void setID(i32 id);
        void setName(const wchar_t *name);
        void setActive(bool a);
        void setPosition(Vector3<f32> pos);
        void setScale(Vector3<f32> s);
        void rotate(f32 x, f32 y);

    private:
        scene::IBillboardSceneNode* billboardNode;
};

#endif