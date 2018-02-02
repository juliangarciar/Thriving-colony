#ifndef MODEL_H
#define MODEL_H

#include <irrlicht.h>
#include "SceneNode.h"
#include "Material.h"
#include "Box3D.h"

using namespace irr;

class Model {
    public:
        Model(int id, const wchar_t *path);
        Model(SceneNode *parent, int id, const wchar_t *path);

        ~Model();

        void setID(int id);
        void setName(const wchar_t *name);
        void setActive(bool a);
        void setMaterial(Material *m);
        void setPosition(Vector3<float> pos);
        void setScale(Vector3<float> s);

        int getID();
        Vector3<float> getPosition();
        Box3D<float> getBoundingBox();
		scene::IMeshSceneNode *getModel();
        
    private:
        scene::IMeshSceneNode *meshNode;
        scene::ITriangleSelector *selector = 0;
};

#endif