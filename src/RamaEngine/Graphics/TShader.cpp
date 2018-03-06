#include "TShader.h"

TShader::TShader(){

}

TShader::~TShader(){
    glDeleteShader(shaderID);
}

void TShader::setShader(ResourceGLSL *s){
    GLint vertexResult = GL_FALSE;
    int vertexInfoLogLength;

    // Read the Vertex Shader code from the file
    if (s->getShaderType() == REEnums::ShaderType::VERTEX){
        shaderID = glCreateShader(GL_VERTEX_SHADER);
    } else {
        shaderID = glCreateShader(GL_FRAGMENT_SHADER);
    }
    
    // Compile Vertex Shader
    char const * VertexSourcePointer = s->getShaderCode().c_str();
    glShaderSource(shaderID, 1, &VertexSourcePointer , NULL);
    glCompileShader(shaderID);

    // Check Vertex Shader
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &vertexResult);
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &vertexInfoLogLength);
    if (vertexInfoLogLength > 0){
        std::vector<char> VertexShaderErrorMessage(vertexInfoLogLength+1);
        glGetShaderInfoLog(shaderID, vertexInfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        std::cout << &VertexShaderErrorMessage[0] << std::endl;
        exit(0);
    }
}

GLuint TShader::getShaderID(){
    return shaderID;
}