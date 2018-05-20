#include "ResourceManager.h"

#include "ResourceOBJ.h"
#include "ResourceMTL.h"
#include "ResourceJSON.h"
#include "ResourceGLSL.h"
#include "ResourceIMG.h"

ResourceManager::ResourceManager() {
    std::string temp[] = {"obj","mtl","json","glsl","bmp","jpg","jpeg","png"};
    supportedFormats.insert(supportedFormats.end(),temp,std::end(temp));
}

ResourceManager::~ResourceManager() {
    //ToDo: recorrer resources y liberarlos
    resources.clear();
}

void ResourceManager::Update() {
    //ToDo: revisar cola de procesos
    threads.front().join();
    threads.pop();
}

void ResourceManager::load(std::string path, bool sync) {
    std::size_t found = path.find_last_of(".");
    std::string extension = path.substr(found+1);

    if (extension.find("obj") != std::string::npos) {
        Resource *r = new ResourceOBJ();
        r -> load(path.c_str());
        resources.insert(std::pair<std::string, Resource*>(path, r));
    } else if (extension.find("mtl") != std::string::npos) {
        Resource *r = new ResourceMTL();
        r -> load(path.c_str());
        resources.insert(std::pair<std::string, Resource*>(path, r));
    } else if (extension.find("json") != std::string::npos) {
        Resource *r = new ResourceJSON();
        r -> load(path.c_str());
        resources.insert(std::pair<std::string, Resource*>(path, r));
    } else if (extension.find("glsl") != std::string::npos) {
        Resource *r = new ResourceGLSL();
        r -> load(path.c_str());
        resources.insert(std::pair<std::string, Resource*>(path, r));
    } else if (extension.find("bmp") != std::string::npos || extension.find("jpg") != std::string::npos || extension.find("jpeg") != std::string::npos || extension.find("png") != std::string::npos) {
        Resource *r = new ResourceIMG();
        r -> load(path.c_str());
        resources.insert(std::pair<std::string, Resource*>(path, r));
    } else {
        std::cout << "Error: extension no soportada (" << extension << ") en el archivo '" << path << "'." << std::endl;
        exit(0);
    }
}

void ResourceManager::push(std::string path) {
	threads.push(std::thread([=]() {
		load(path, false);
	}));
}

void ResourceManager::loadResource(std::string path, bool sync) {
	if (path.find(".") != std::string::npos) {
		if (sync) {
			load(path, true);
		} else {
			push(path);
		}
	} else {
        std::cout << "Error: no se puede leer el archivo " << path << std::endl;
        exit(0);
	}
}

Resource *ResourceManager::getResource(std::string path, bool sync) {
	if (path.find(".") != std::string::npos) {
		std::map<std::string, Resource*>::iterator it;
		it = resources.find(path);
		if (it != resources.end()) {
			return it -> second;
		} else {
			loadResource(path, sync);
			if (sync) return getResource(path);
			else return nullptr;
		}
	} else {
        std::cout << "Error: no se puede leer el archivo " << path << std::endl;
        exit(0);
	}
}

//ToDo: release resource