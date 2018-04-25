#ifndef MODEL_H
#define MODEL_H

#include <cmath>
#include <OBDEngine/OBDObject.h>

#include <Types.h>
#include <GraphicEngine/SceneNode.h>
#include <GraphicEngine/Material.h>

class Model {
    public:
        Model(i32 id, std::string path);
        Model(SceneNode *parent, i32 id, std::string path);

        ~Model();

        void setID(i32 id);
        void setName(const char *name);
        void setActive(bool a);
        void setMaterial(Material *m);
        void setPosition(Vector3<f32> pos);
        void setScale(Vector3<f32> s);
        void rotate(f32 x, f32 y);
        i32 getID();
        Vector3<f32> getPosition();
		//scene::IMeshSceneNode *getModel();
        
    private:
        OBDObject *obj;
};

#endif