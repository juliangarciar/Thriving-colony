#ifndef MODEL_H
#define MODEL_H

#include <irrlicht.h>
#include "SceneNode.h"

using namespace irr;

class Model {
    public:
        Model(int id);
        Model(SceneNode *parent, int id);
        ~Model();

        void setID(int id);
        void setName(const wchar_t *name);
        void setActive(bool a);

        void setPosition(Vector3<float> pos);
        Vector3<float> getPosition();

        int getID();
		scene::IMeshSceneNode *getModel();
    private:
        scene::IMeshSceneNode *cubeNode;
        scene::ITriangleSelector *selector = 0;
};

#endif