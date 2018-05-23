#ifndef OBDSOURCEOBJ_H
#define OBDSOURCEOBJ_H

#include "Resource.h"
#include "ResourceManager.h"

struct ResourceMesh {
    std::string name;
    // Buffers
    std::vector<f32> *vbo;
    std::vector<u32> *ibo;
    // Buffer ids
	GLuint VAO;
	GLuint VBO;
	GLuint IBO;

    std::string defaultMaterialName;
    // Bounding box
    glm::vec3 aabbMin;
	glm::vec3 aabbMax;
	
	bool isSetup;
};

class ResourceOBJ : public Resource {
    public:
        /**
         * @brief Construct a new Resource O B J object
         * 
         */
        ResourceOBJ();
        /**
         * @brief Destroy the Resource O B J object
         * 
         */
        ~ResourceOBJ();
        /**
         * @brief load the obj file
         * 
         * @param path path to file
         */
        void load(const char *path);
        /**
         * @brief release this resource, freeing up the memory it occupied.
         * 
         */
        void release();

        /**
         * @brief Prepare the mesh to be used later
         * 
         * @param mesh 
         */
		void setupMesh(ResourceMesh *mesh);

        /**
         * @brief Set the ID
         * 
         */
        void setIdentifier(const char *);

        /**
         * @brief returns the id of the resource
         * 
         * @return const char* 
         */
        const char *getIdentifier();

        /**
         * @brief Get the Resource object
         * 
         * @return std::map<std::string, ResourceMesh*>* mesh Array wth all the data relative to this resource
         */
        std::map<std::string, ResourceMesh*> *getResource();

        /**
         * @brief Get the Default Material Path
         * 
         * @return std::string 
         */
        std::string getDefaultMaterialPath();
    private:

        std::map<std::string, ResourceMesh*> *meshArray;
        std::string defaultMaterialPath;
};

#endif