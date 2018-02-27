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
        // Read the Vertex Shader code from the file
        shaderID = glCreateShader(GL_VERTEX_SHADER);
        std::string VertexShaderCode;
        std::ifstream VertexShaderStream(file_path, std::ios::in);
        if (VertexShaderStream.is_open()) {
            std::stringstream sstr;
            sstr << VertexShaderStream.rdbuf();
            VertexShaderCode = sstr.str();
            VertexShaderStream.close();
        } else {
            std::cout << "Impossible to open " << file_path << ". Are you in the right directory?" << std::endl;
            return;
        }

        GLint vertexResult = GL_FALSE;
        int vertexInfoLogLength;

        // Compile Vertex Shader
        std::cout << "Compiling shader: " << file_path << std::endl;
        char const * VertexSourcePointer = VertexShaderCode.c_str();
        glShaderSource(shaderID, 1, &VertexSourcePointer , NULL);
        glCompileShader(shaderID);

        // Check Vertex Shader
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &vertexResult);
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &vertexInfoLogLength);
        if (vertexInfoLogLength > 0){
            std::vector<char> VertexShaderErrorMessage(vertexInfoLogLength+1);
            glGetShaderInfoLog(shaderID, vertexInfoLogLength, NULL, &VertexShaderErrorMessage[0]);
            std::cout << &VertexShaderErrorMessage[0] << std::endl;
            return;
        }

        type = ShaderType::VERTEX;
    } else if (fragmentFound != std::string::npos) {
        // Read the Fragment Shader code from the file
        shaderID = glCreateShader(GL_FRAGMENT_SHADER);
        std::string FragmentShaderCode;
        std::ifstream FragmentShaderStream(file_path, std::ios::in);
        if(FragmentShaderStream.is_open()){
            std::stringstream sstr;
            sstr << FragmentShaderStream.rdbuf();
            FragmentShaderCode = sstr.str();
            FragmentShaderStream.close();
        } else {
            std::cout << "Impossible to open " << file_path << ". Are you in the right directory?" << std::endl;
            return;
        }

        GLint fragmentResult = GL_FALSE;
        int fragmentInfoLogLength;

        // Compile Fragment Shader
        std::cout << "Compiling shader: " << file_path << std::endl;
        char const * FragmentSourcePointer = FragmentShaderCode.c_str();
        glShaderSource(shaderID, 1, &FragmentSourcePointer , NULL);
        glCompileShader(shaderID);

        // Check Fragment Shader
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &fragmentResult);
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &fragmentInfoLogLength);
        if (fragmentInfoLogLength > 0){
            std::vector<char> FragmentShaderErrorMessage(fragmentInfoLogLength+1);
            glGetShaderInfoLog(shaderID, fragmentInfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
            std::cout << &FragmentShaderErrorMessage[0] << std::endl;
            return;
        }
        
        type = ShaderType::FRAGMENT;
    } else {
        std::cout << "Error, unknown shader type." << std::endl;
    }
}

void ResourceGLSL::release(){
    glDeleteShader(shaderID);
}

void ResourceGLSL::setIdentifier(const char *i){
    identifier = i;
}

const char *ResourceGLSL::getIdentifier(){
    return identifier;
}

GLuint ResourceGLSL::getShaderID(){
    return shaderID;
}