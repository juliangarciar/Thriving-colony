#ifndef RESOURCEOBJ_H
#define RESOURCEOBJ_H

#include "Resource.h"
#include <OurEngine/TResourceMesh.h>
#include <OurEngine/TMaterial.h>
#include <MathEngine/Vector2.h>
#include <MathEngine/Vector3.h>

class ResourceOBJ : public Resource {
    public:
        ResourceOBJ();
        ~ResourceOBJ();

        void load(const char *path);

        void setIdentifier(const char *);
        const char *getIdentifier();

        std::vector<TResourceMesh*> *getOBJMesh();
    private:
        std::vector<TResourceMesh*> objMesh;
};

#endif