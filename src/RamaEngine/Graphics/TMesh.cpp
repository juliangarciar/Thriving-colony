#include "TMesh.h"

#include "../ResourceManager/ResourceOBJ.h"

TMesh::TMesh(TResourceMesh *r) : TEntity() {
	mesh = r;

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, mesh->getVertices().size() * sizeof(glm::vec3), &mesh->getVertices()[0], GL_STATIC_DRAW);

	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, mesh->getNormals().size() * sizeof(glm::vec3), &mesh->getNormals()[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, mesh->getTextureCoordinates().size() * sizeof(glm::vec2), &mesh->getTextureCoordinates()[0], GL_STATIC_DRAW);
	
	// Generate a buffer for the indices as well
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->getIndices().size() * sizeof(unsigned short), &mesh->getIndices()[0] , GL_STATIC_DRAW);
}

TMesh::~TMesh() {
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteBuffers(1, &normalbuffer);
	glDeleteBuffers(1, &elementbuffer);
}

void TMesh::beginDraw() {    
    TMatrixCache *cache = TMatrixCache::Instance();

	glm::mat4 pM = *cache->getMatrix(REEnums::Matrices::MATRIX_PROJECTION);
	glm::mat4 vM = *cache->getMatrix(REEnums::Matrices::MATRIX_VIEW);
	glm::mat4 mM = *cache->getMatrix(REEnums::Matrices::MATRIX_MODEL);
	mM = glm::mat4(1.0f); //ToDo: aqui esta roto

	// Matrices
	glm::mat4 MV = vM * mM;
	glm::mat4 MVP = pM * vM * mM;
	glUniformMatrix4fv(cache->getMatrixID(REEnums::Matrices::MATRIX_MODEL), 1, GL_FALSE, &mM[0][0]);
	glUniformMatrix4fv(cache->getMatrixID(REEnums::Matrices::MATRIX_VIEW), 1, GL_FALSE, &vM[0][0]);
	glUniformMatrix4fv(cache->getMatrixID(REEnums::Matrices::MATRIX_PROJECTION), 1, GL_FALSE, &pM[0][0]);
	glUniformMatrix4fv(cache->getMatrixID(REEnums::Matrices::MATRIX_VIEWMODEL), 1, GL_FALSE, &MV[0][0]);
	glUniformMatrix4fv(cache->getMatrixID(REEnums::Matrices::MATRIX_MVP), 1, GL_FALSE, &MVP[0][0]);

	glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mesh->getMaterial()->getDiffuseTextureMap()->getTextureID());
    glUniform1i(cache->getMatrixID(REEnums::Matrices::MATRIX_TEXTURE), 0);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// 3rd attribute buffer : normals
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glVertexAttribPointer(
		2,                                // attribute
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// Index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

	// Draw the triangles !
	glDrawElements(
		GL_TRIANGLES,      // mode
		mesh->getIndices().size(),    // count
		GL_UNSIGNED_SHORT,   // type
		(void*)0           // element array buffer offset
	);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void TMesh::endDraw() {

}