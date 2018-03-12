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
    TMatrixCache *cache = TMatrixCache::Instance();
	cache->setMatrixID(REEnums::Matrices::MATRIX_MVP, myMVP);
	cache->setMatrixID(REEnums::Matrices::MATRIX_MVP, myProjection);
	cache->setMatrixID(REEnums::Matrices::MATRIX_MVP, myView);
	cache->setMatrixID(REEnums::Matrices::MATRIX_MVP, myModel);
	cache->setMatrixID(REEnums::Matrices::MATRIX_MVP, myTexture);
}

void TRoot::endDraw(){

}