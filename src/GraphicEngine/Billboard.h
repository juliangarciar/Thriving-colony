#ifndef BILLBOARD_H
#define BILLBOARD_H

#include <Types.h>
#include "SceneNode.h"
#include <MathEngine/Vector3.h>
#include <MathEngine/Color.h>
#include <OBDEngine/OBDBillboard.h>

class Billboard {
    public:
        Billboard(SceneNode* parent, Vector3<f32> pos, Vector2<f32> size, Color back, Color front);
        ~Billboard();

        void setColor(Color);
        void setFrontColor(Color);
        void setPosition(Vector3<f32> pos);
        void setSize(Vector2<f32>);
		void setFrontWidth(f32);
        void setActive(bool a);

        Vector3<f32> getPosition();
    private:
        OBDBillboard* billboard;
};

#endif