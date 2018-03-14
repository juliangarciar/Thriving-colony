#include "ResourceManager.h"

#include "ResourceOBJ.h"
#include "ResourceJSON.h"
#include "ResourceGLSL.h"
#include "ResourceIMG.h"

ResourceManager::ResourceManager(){
    std::string temp[8] = {"obj","json","glsl","fbx","bmp","jpg","jpeg","png"};
    supportedFormats.insert(supportedFormats.end(),temp,std::end(temp));
}

ResourceManager::~ResourceManager(){
    resources.clear();
}

void ResourceManager::Update(){
    //ToDo: ¿esto es asi?
    threads.front().join();
    threads.pop();
}

void ResourceManager::load(std::string path, bool sync){
    std::size_t found = path.find_last_of(".");
    std::string extension = path.substr(found+1);
    if (extension == "obj"){
        Resource *r = new ResourceOBJ(this);
        r -> load(path.c_str(), sync);
        resources.insert(std::pair<std::string, Resource*>(path, r));
    } else if (extension == "json") {
        Resource *r = new ResourceJSON(this);
        r -> load(path.c_str(), sync);
        resources.insert(std::pair<std::string, Resource*>(path, r));
    } else if (extension == "glsl") {
        Resource *r = new ResourceGLSL(this);
        r -> load(path.c_str(), sync);
        resources.insert(std::pair<std::string, Resource*>(path, r));
    } else if (extension == "fbx"){
        //Resource *r = new ResourceFBX();
        //r -> load(path.c_str());
        //resources.insert(std::pair<std::string, Resource*>(path, r));
    } else if (extension == "bmp" || extension == "jpg" || extension == "jpeg" || extension == "png"){
        Resource *r = new ResourceIMG(this);
        r -> load(path.c_str(), sync);
        resources.insert(std::pair<std::string, Resource*>(path, r));
    } else {
        std::cout << "Error: formato no soportado" << std::endl;
        exit(0);
    }
}

void ResourceManager::push(std::string path){
    std::size_t found = path.find_last_of(".");
    std::string extension = path.substr(found+1);
    std::vector<std::string>::iterator it;
    it = find(supportedFormats.begin(),supportedFormats.end(),extension);
    if (it != supportedFormats.end()){
        threads.push(std::thread([=](){
            load(path, false);
        }));
    } else {
        std::cout << "Error: formato no soportado" << std::endl;
        exit(0);
    }
}

void ResourceManager::loadResource(std::string path, bool sync){
    if (sync){
        load(path, true);
    } else {
        push(path);
    }
}

Resource *ResourceManager::getResource(std::string path, bool sync){
    std::map<std::string, Resource*>::iterator it;
    it = resources.find(path);
    if (it != resources.end()){
        return it -> second;
    } else {
        loadResource(path, sync);
        if (sync) return getResource(path);
        else return nullptr;
    }
}