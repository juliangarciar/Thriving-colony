#ifndef MODEL_H
#define MODEL_H

#include <irrlicht.h>
#include "SceneNode.h"

using namespace irr;

class Model {
    public:
        Model();
        Model(SceneNode *parent);
        ~Model();

		scene::IMeshSceneNode *getModel();
    private:
        scene::IMeshSceneNode *cubeNode;
        scene::ITriangleSelector *selector = 0;
};

#endif