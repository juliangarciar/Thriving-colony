#include "ResourceManager.h"

ResourceManager::ResourceManager(){
    
}

ResourceManager::~ResourceManager(){
    resources.clear();
}

void ResourceManager::Update(){
    //ToDo: ¿esto es asi?
    threads.front().join();
    threads.pop();
}

void ResourceManager::load(std::string path){
    std::size_t found = path.find_last_of(".");
    std::string extension = path.substr(found+1);
    if (extension == "obj"){
        Resource *r = new ResourceOBJ();
        r -> load(path.c_str());
        resources.insert(std::pair<std::string, Resource*>(path, r));
    } else if (extension == "fbx"){
    /* Resource *r = new ResourceOBJ();
        r -> load(path.c_str());
        resources.insert(std::pair<std::string, Resource*>(path, r));*/
    } else if (extension == "jpg"){
        /*Resource *r = new ResourceOBJ();
        r -> load(path.c_str());
        resources.insert(std::pair<std::string, Resource*>(path, r));*/
    } else if (extension == "png"){
        /*Resource *r = new ResourceOBJ();
        r -> load(path.c_str());
        resources.insert(std::pair<std::string, Resource*>(path, r));*/
    } else if (extension == "bmp"){
        /*Resource *r = new ResourceOBJ();
        r -> load(path.c_str());
        resources.insert(std::pair<std::string, Resource*>(path, r));*/
    } else if (extension == "json") {
        Resource *r = new ResourceJSON();
        r -> load(path.c_str());
        resources.insert(std::pair<std::string, Resource*>(path, r));
    } else {
        std::cout << "Error: formato no soportado" << std::endl;
        exit(0);
    }
}

void ResourceManager::push(std::string path){
    std::size_t found = path.find_last_of(".");
    std::string extension = path.substr(found+1);
    if (extension == "obj" | extension == "fbx" | extension == "jpg" | extension == "png" | extension == "bmp" | extension == "json"){
        threads.push(std::thread([=](){
            load(path);
        }));
    } else {
        std::cout << "Error: formato no soportado" << std::endl;
        exit(0);
    }
}

void ResourceManager::loadResource(std::string path, bool sync){
    if (sync){
        load(path);
    } else {
        push(path);
    }
}

Resource *ResourceManager::getResource(std::string path){
    std::map<std::string, Resource*>::iterator it;
    it = resources.find(path);
    if (it != resources.end()){
        return it -> second;
    } else {
        loadResource(path, false);
        return nullptr;
    }
}