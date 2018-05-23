#ifndef OBDSOURCEOBJ_H
#define OBDSOURCEOBJ_H

#include "Resource.h"
#include "ResourceManager.h"

struct ResourceMesh {
    std::string name;

    std::vector<f32> *vbo;
    std::vector<u32> *ibo;

	GLuint VAO;
	GLuint VBO;
	GLuint IBO;

    std::string defaultMaterialName;

    glm::vec3 aabbMin;
	glm::vec3 aabbMax;
	
	bool isSetup;
};

class ResourceOBJ : public Resource {
    public:
        ResourceOBJ();
        ~ResourceOBJ();

        void load(const char *path);
        void release();

		void setupMesh(ResourceMesh *mesh);

        void setIdentifier(const char *);
        const char *getIdentifier();

        std::map<std::string, ResourceMesh*> *getResource();

        std::string getDefaultMaterialPath();
    private:

        std::map<std::string, ResourceMesh*> *meshArray;
        std::string defaultMaterialPath;
};

#endif