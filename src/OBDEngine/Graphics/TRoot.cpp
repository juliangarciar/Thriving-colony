#include "TRoot.h"

TRoot::TRoot(GLuint programID) : TEntity() {
	// Get a handle for our "MVP" uniform
	matrixIDs[OBDEEnums::Matrices::MATRIX_MVP] = glGetUniformLocation(programID, "MVP");
    matrixIDs[OBDEEnums::Matrices::MATRIX_PROJECTION] = glGetUniformLocation(programID, "P");
	matrixIDs[OBDEEnums::Matrices::MATRIX_VIEW] = glGetUniformLocation(programID, "V");
	matrixIDs[OBDEEnums::Matrices::MATRIX_MODEL] = glGetUniformLocation(programID, "M");
	matrixIDs[OBDEEnums::Matrices::MATRIX_VIEWMODEL] = glGetUniformLocation(programID, "VM");

	matrixIDs[OBDEEnums::Matrices::MATRIX_LIGHT] = glGetUniformLocation(programID, "lightPosition_worldspace");
	
	matrixIDs[OBDEEnums::Matrices::MATRIX_TEXTURE_AMBIENT] = glGetUniformLocation(programID, "textureSamplerAmbient");
	matrixIDs[OBDEEnums::Matrices::MATRIX_TEXTURE_DIFFUSE] = glGetUniformLocation(programID, "textureSamplerDiffuse");
	matrixIDs[OBDEEnums::Matrices::MATRIX_TEXTURE_SPECULAR] = glGetUniformLocation(programID, "textureSamplerSpecular");
	matrixIDs[OBDEEnums::Matrices::MATRIX_TEXTURE_ALPHA] = glGetUniformLocation(programID, "textureSamplerAlpha");
	matrixIDs[OBDEEnums::Matrices::MATRIX_TEXTURE_BUMP] = glGetUniformLocation(programID, "textureSamplerBump");
}

TRoot::~TRoot() {
    
}

void TRoot::beginDraw(){
    TMatrixCache *cache = TMatrixCache::Instance();
	cache->setMatrixID(OBDEEnums::Matrices::MATRIX_MVP, matrixIDs[OBDEEnums::Matrices::MATRIX_MVP]);
	cache->setMatrixID(OBDEEnums::Matrices::MATRIX_PROJECTION, matrixIDs[OBDEEnums::Matrices::MATRIX_PROJECTION]);
	cache->setMatrixID(OBDEEnums::Matrices::MATRIX_VIEW, matrixIDs[OBDEEnums::Matrices::MATRIX_VIEW]);
	cache->setMatrixID(OBDEEnums::Matrices::MATRIX_MODEL, matrixIDs[OBDEEnums::Matrices::MATRIX_MODEL]);
	cache->setMatrixID(OBDEEnums::Matrices::MATRIX_VIEWMODEL, matrixIDs[OBDEEnums::Matrices::MATRIX_VIEWMODEL]);

	cache->setMatrixID(OBDEEnums::Matrices::MATRIX_LIGHT, matrixIDs[OBDEEnums::Matrices::MATRIX_LIGHT]);

	cache->setMatrixID(OBDEEnums::Matrices::MATRIX_TEXTURE_AMBIENT, matrixIDs[OBDEEnums::Matrices::MATRIX_TEXTURE_AMBIENT]);
	cache->setMatrixID(OBDEEnums::Matrices::MATRIX_TEXTURE_DIFFUSE, matrixIDs[OBDEEnums::Matrices::MATRIX_TEXTURE_DIFFUSE]);
	cache->setMatrixID(OBDEEnums::Matrices::MATRIX_TEXTURE_SPECULAR, matrixIDs[OBDEEnums::Matrices::MATRIX_TEXTURE_SPECULAR]);
	cache->setMatrixID(OBDEEnums::Matrices::MATRIX_TEXTURE_ALPHA, matrixIDs[OBDEEnums::Matrices::MATRIX_TEXTURE_ALPHA]);
	cache->setMatrixID(OBDEEnums::Matrices::MATRIX_TEXTURE_BUMP, matrixIDs[OBDEEnums::Matrices::MATRIX_TEXTURE_BUMP]);
}

void TRoot::endDraw(){

}