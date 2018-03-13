#include "TRoot.h"

TRoot::TRoot(GLuint programID) : TEntity() {
	// Get a handle for our "MVP" uniform
	myMVP = glGetUniformLocation(programID, "MVP");
    myProjection = glGetUniformLocation(programID, "P");
	myView = glGetUniformLocation(programID, "V");
	myModel = glGetUniformLocation(programID, "M");
	myViewModel = glGetUniformLocation(programID, "VM");
	
	myTexture = glGetUniformLocation(programID, "textureSampler");
    myLight = glGetUniformLocation(programID, "lightPosition_worldspace");
}

TRoot::~TRoot() {
    
}

void TRoot::beginDraw(){
    TMatrixCache *cache = TMatrixCache::Instance();
	cache->setMatrixID(REEnums::Matrices::MATRIX_MVP, myMVP);
	cache->setMatrixID(REEnums::Matrices::MATRIX_PROJECTION, myProjection);
	cache->setMatrixID(REEnums::Matrices::MATRIX_VIEW, myView);
	cache->setMatrixID(REEnums::Matrices::MATRIX_MODEL, myModel);
	cache->setMatrixID(REEnums::Matrices::MATRIX_VIEWMODEL, myViewModel);
	cache->setMatrixID(REEnums::Matrices::MATRIX_TEXTURE, myTexture);
	cache->setMatrixID(REEnums::Matrices::MATRIX_LIGHT, myLight);
}

void TRoot::endDraw(){

}