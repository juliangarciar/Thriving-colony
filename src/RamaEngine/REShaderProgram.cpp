#include "REShaderProgram.h"

REShaderProgram::REShaderProgram(ResourceGLSL* vs, ResourceGLSL* fs){
	vertexShader = new TShader();
	vertexShader->setShader(vs);
	fragmentShader = new TShader();
	fragmentShader->setShader(fs);

	pid = glCreateProgram();
	glAttachShader(pid, vertexShader->getShaderID());
	glAttachShader(pid, fragmentShader->getShaderID());
}

REShaderProgram::~REShaderProgram(){
	glDetachShader(pid, vertexShader->getShaderID());
	glDeleteShader(vertexShader->getShaderID());
	glDetachShader(pid, fragmentShader->getShaderID());
	glDeleteShader(fragmentShader->getShaderID());
}
    
GLuint REShaderProgram::getShaderProgram(){
	return pid;
}