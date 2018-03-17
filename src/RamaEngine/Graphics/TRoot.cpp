#include "TRoot.h"

TRoot::TRoot(GLuint programID) : TEntity() {
	// Get a handle for our "MVP" uniform
	matrixIDs[REEnums::Matrices::MATRIX_MVP] = glGetUniformLocation(programID, "MVP");
    matrixIDs[REEnums::Matrices::MATRIX_PROJECTION] = glGetUniformLocation(programID, "P");
	matrixIDs[REEnums::Matrices::MATRIX_VIEW] = glGetUniformLocation(programID, "V");
	matrixIDs[REEnums::Matrices::MATRIX_MODEL] = glGetUniformLocation(programID, "M");
	matrixIDs[REEnums::Matrices::MATRIX_VIEWMODEL] = glGetUniformLocation(programID, "VM");

	matrixIDs[REEnums::Matrices::MATRIX_LIGHT] = glGetUniformLocation(programID, "lightPosition_worldspace");
	
	matrixIDs[REEnums::Matrices::MATRIX_TEXTURE_AMBIENT] = glGetUniformLocation(programID, "textureSamplerAmbient");
	matrixIDs[REEnums::Matrices::MATRIX_TEXTURE_DIFFUSE] = glGetUniformLocation(programID, "textureSamplerDiffuse");
	matrixIDs[REEnums::Matrices::MATRIX_TEXTURE_SPECULAR] = glGetUniformLocation(programID, "textureSamplerSpecular");
	matrixIDs[REEnums::Matrices::MATRIX_TEXTURE_ALPHA] = glGetUniformLocation(programID, "textureSamplerAlpha");
	matrixIDs[REEnums::Matrices::MATRIX_TEXTURE_BUMP] = glGetUniformLocation(programID, "textureSamplerBump");
}

TRoot::~TRoot() {
    
}

void TRoot::beginDraw(){
    TMatrixCache *cache = TMatrixCache::Instance();
	cache->setMatrixID(REEnums::Matrices::MATRIX_MVP, matrixIDs[REEnums::Matrices::MATRIX_MVP]);
	cache->setMatrixID(REEnums::Matrices::MATRIX_PROJECTION, matrixIDs[REEnums::Matrices::MATRIX_PROJECTION]);
	cache->setMatrixID(REEnums::Matrices::MATRIX_VIEW, matrixIDs[REEnums::Matrices::MATRIX_VIEW]);
	cache->setMatrixID(REEnums::Matrices::MATRIX_MODEL, matrixIDs[REEnums::Matrices::MATRIX_MODEL]);
	cache->setMatrixID(REEnums::Matrices::MATRIX_VIEWMODEL, matrixIDs[REEnums::Matrices::MATRIX_VIEWMODEL]);

	cache->setMatrixID(REEnums::Matrices::MATRIX_LIGHT, matrixIDs[REEnums::Matrices::MATRIX_LIGHT]);

	cache->setMatrixID(REEnums::Matrices::MATRIX_TEXTURE_AMBIENT, matrixIDs[REEnums::Matrices::MATRIX_TEXTURE_AMBIENT]);
	cache->setMatrixID(REEnums::Matrices::MATRIX_TEXTURE_DIFFUSE, matrixIDs[REEnums::Matrices::MATRIX_TEXTURE_DIFFUSE]);
	cache->setMatrixID(REEnums::Matrices::MATRIX_TEXTURE_SPECULAR, matrixIDs[REEnums::Matrices::MATRIX_TEXTURE_SPECULAR]);
	cache->setMatrixID(REEnums::Matrices::MATRIX_TEXTURE_ALPHA, matrixIDs[REEnums::Matrices::MATRIX_TEXTURE_ALPHA]);
	cache->setMatrixID(REEnums::Matrices::MATRIX_TEXTURE_BUMP, matrixIDs[REEnums::Matrices::MATRIX_TEXTURE_BUMP]);
}

void TRoot::endDraw(){

}