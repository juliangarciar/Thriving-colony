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

		scene::IMeshSceneNode *getModel();
    private:
        scene::IMeshSceneNode *cubeNode;
        scene::ITriangleSelector *selector = 0;
};

#endif