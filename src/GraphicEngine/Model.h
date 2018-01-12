#ifndef MODEL_H
#define MODEL_H

#include <irrlicht.h>
#include "SceneNode.h"

using namespace irr;

class Model {
    public:
        Model(int id, int size);
        Model(SceneNode *parent, int id, int size);

        Model(int id, const wchar_t *path);
        Model(SceneNode *parent, int id, const wchar_t *path);

        ~Model();

        void setID(int id);
        void setName(const wchar_t *name);
        void setActive(bool a);

        void setPosition(Vector3<float> pos);
        Vector3<float> getPosition();

        int getID();
		scene::IMeshSceneNode *getModel();
    private:
        scene::IMeshSceneNode *meshNode;
        scene::ITriangleSelector *selector = 0;
};

#endif