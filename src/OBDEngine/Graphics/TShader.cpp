#include "TShader.h"

TShader::TShader(ResourceGLSL *s){
    GLint shaderResult = GL_FALSE;
    int shaderInfoLogLength;

    // Read the shader Shader code from the file
    if (s->getShaderType() == OBDEnums::ShaderType::VERTEX){
        shaderID = glCreateShader(GL_VERTEX_SHADER);
    } else {
        shaderID = glCreateShader(GL_FRAGMENT_SHADER);
    }
    
    // Compile shader Shader
    const char *shaderSourcePointer = s->getShaderCode()->c_str();
    glShaderSource(shaderID, 1, &shaderSourcePointer , NULL);
    glCompileShader(shaderID);

    // Check shader Shader
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &shaderResult);
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &shaderInfoLogLength);
    if (shaderInfoLogLength > 0){
        std::vector<char> shaderErrorMessage(shaderInfoLogLength+1);
        glGetShaderInfoLog(shaderID, shaderInfoLogLength, NULL, &shaderErrorMessage[0]);
        std::cout << &shaderErrorMessage[0] << std::endl;
        exit(0);
    }
}

TShader::~TShader(){
    glDeleteShader(shaderID);
}

GLuint TShader::getShaderID(){
    return shaderID;
}