#ifndef MODEL_H
#define MODEL_H

#include <cmath>
#include <OBDEngine/OBDObject.h>

#include <Types.h>
#include <GraphicEngine/SceneNode.h>
#include <GraphicEngine/Material.h>
#include <MathEngine/Color.h>

class Model {
    public:
        Model(i32 id, std::string path);
        Model(SceneNode *parent, i32 id, std::string path);
        ~Model();

        void setID(i32 id);
        void setActive(bool a);
        void setMaterial(Material *m);
		void setColor(Color);
        void setPosition(Vector3<f32> pos);
        void setRotation(Vector3<f32> r);
        void setScale(Vector3<f32> s);

        i32 getID();
        Vector3<f32> getPosition();
        Vector3<f32> getRotation();
    private:
        OBDObject *obj;
		Material *material;
};

#endif