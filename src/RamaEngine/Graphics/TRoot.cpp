#include "TRoot.h"

TRoot::TRoot(GLuint programID) : TEntity() {
	// Get a handle for our "MVP" uniform
	myMVP = glGetUniformLocation(programID, "MVP");
    myProjection = glGetUniformLocation(programID, "P");
	myView = glGetUniformLocation(programID, "V");
	myModel = glGetUniformLocation(programID, "M");
	
	// Get a handle for our "myTextureSampler" uniform
	myTexture = glGetUniformLocation(programID, "Texture");
}

TRoot::~TRoot() {
    
}

void TRoot::beginDraw(){
	MVPID = myMVP;
	projectionMatrixID = myProjection;
	viewMatrixID = myView;
	modelMatrixID = myModel;
	textureID = myTexture;
}

void TRoot::endDraw(){

}