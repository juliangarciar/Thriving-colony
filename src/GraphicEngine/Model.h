#ifndef MODEL_H
#define MODEL_H

#include <irrlicht/irrlicht.h>
#include <Types.h>
#include <GraphicEngine/SceneNode.h>
#include <GraphicEngine/Material.h>
#include <MathEngine/Color.h>

using namespace irr;

class Model {
    public:
        Model(i32 id, std::string path);
        Model(SceneNode *parent, i32 id, std::string path);

        ~Model();

        void setID(i32 id);
        void setName(const char *name);
        void setActive(bool a);
        void setMaterial(Material *m);
		void setColor(Color);
        void setPosition(Vector3<f32> p);
        void setScale(Vector3<f32> s);
        void setRotation(Vector3<f32> r);
        i32 getID();
        Vector3<f32> getPosition();
        Vector3<f32> getRotation();
		scene::IMeshSceneNode *getModel();
        
    private:
        scene::IMeshSceneNode *meshNode;
        scene::ITriangleSelector *selector = 0;

        i32 startingFrame;
        i32 endingFrame;
        i32 currentFrame;

		Material *material;
};

#endif