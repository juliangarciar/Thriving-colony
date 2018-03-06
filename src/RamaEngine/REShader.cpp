#include "REShader.h"

REShader::REShader(ResourceGLSL* s, GLuint p){
	shader = new TShader();
	shader->setShader(s);

	pid = p;

	glAttachShader(pid, shader->getShaderID());
}

REShader::~REShader(){
	glDetachShader(pid, shader->getShaderID());
	glDeleteShader(shader->getShaderID());
}
    
TShader *REShader::loadShader(){
	return shader;
}