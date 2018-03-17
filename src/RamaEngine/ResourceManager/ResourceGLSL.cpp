#include "ResourceGLSL.h"

ResourceGLSL::ResourceGLSL(){

}

ResourceGLSL::~ResourceGLSL(){
	
}

void ResourceGLSL::load(const char *path){
    setIdentifier(path);
    std::string file_path(path);
    
    std::size_t vertexFound = file_path.find("vertex");
    std::size_t fragmentFound = file_path.find("fragment");

    if (vertexFound != std::string::npos) {
        type = REEnums::ShaderType::VERTEX;
    } else if (fragmentFound != std::string::npos) {
        type = REEnums::ShaderType::FRAGMENT;
    } else {
        std::cout << "Error, unknown shader type." << std::endl;
        exit(0);
    }

    std::ifstream shaderStream(file_path, std::ios::in);
    if (shaderStream.is_open()) {
        std::stringstream sstr;
        sstr << shaderStream.rdbuf();
        shaderCode = sstr.str();
        shaderStream.close();
    } else {
        std::cout << "Impossible to open " << file_path << ". Are you in the right directory?" << std::endl;
        exit(0);
    }
}

void ResourceGLSL::release(){
}

void ResourceGLSL::setIdentifier(const char *i){
    identifier = i;
}

const char *ResourceGLSL::getIdentifier(){
    return identifier;
}

std::string *ResourceGLSL::getShaderCode(){
    return &shaderCode;
}

REEnums::ShaderType ResourceGLSL::getShaderType(){
    return type;
}