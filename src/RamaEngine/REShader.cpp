#include "REShader.h"

REShader::REShader(std::string){
	// Create and compile our GLSL program from the shaders
    /*ResourceGLSL *s = (ResourceGLSL*)r->getResource("vertexShader.glsl", true);
    ResourceGLSL *s2 = (ResourceGLSL*)r->getResource("fragmentShader.glsl", true);

    // Link the program
	programID = glCreateProgram();
	glAttachShader(programID, s->getShaderID());
	glAttachShader(programID, s2->getShaderID());
	glLinkProgram(programID);

	// Check the program
    GLint Result = GL_FALSE;
    int InfoLogLength;
	glGetProgramiv(programID, GL_LINK_STATUS, &Result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(programID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		std::cout << &ProgramErrorMessage[0] << std::endl;
	}

	glDetachShader(programID, s->getShaderID());
	glDetachShader(programID, s2->getShaderID());
	
	glDeleteShader(s->getShaderID());
	glDeleteShader(s2->getShaderID());*/
}

REShader::~REShader(){
	
}
    
TShader *REShader::loadShader(){
	return shader;
}