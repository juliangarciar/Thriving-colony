#include "TMesh.h"

#include "../ResourceManager/ResourceOBJ.h"

TMesh::TMesh(ResourceMesh *r, ResourceMaterial *m) : TEntity() {
	mesh = r;
	material = m;

	// Generate a buffer for the vertices
	glGenBuffers(1, &VBOID);
	glBindBuffer(GL_ARRAY_BUFFER, VBOID);
	glBufferData(GL_ARRAY_BUFFER, mesh->getVBO().size() * sizeof(f32), &mesh->getVBO()[0], GL_STATIC_DRAW);
	
	// Generate a buffer for the indices as well
	glGenBuffers(1, &IBOID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBOID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->getIndices().size() * sizeof(us32), &mesh->getIndices()[0] , GL_STATIC_DRAW);
}

TMesh::~TMesh() {
	glDeleteBuffers(1, &VBOID);
	glDeleteBuffers(1, &IBOID);
}

void TMesh::beginDraw() {    
    TMatrixCache *cache = TMatrixCache::Instance();

	glm::mat4 pM = *cache->getMatrix(REEnums::Matrices::MATRIX_PROJECTION);
	glm::mat4 vM = *cache->getMatrix(REEnums::Matrices::MATRIX_VIEW);
	glm::mat4 mM = cache->getCurrentMatrix();

	// Matrices
	glm::mat4 MV = vM * mM;
	glm::mat4 MVP = pM * vM * mM;
	glUniformMatrix4fv(cache->getMatrixID(REEnums::Matrices::MATRIX_MODEL), 1, GL_FALSE, &mM[0][0]);
	glUniformMatrix4fv(cache->getMatrixID(REEnums::Matrices::MATRIX_VIEW), 1, GL_FALSE, &vM[0][0]);
	glUniformMatrix4fv(cache->getMatrixID(REEnums::Matrices::MATRIX_PROJECTION), 1, GL_FALSE, &pM[0][0]);
	glUniformMatrix4fv(cache->getMatrixID(REEnums::Matrices::MATRIX_VIEWMODEL), 1, GL_FALSE, &MV[0][0]);
	glUniformMatrix4fv(cache->getMatrixID(REEnums::Matrices::MATRIX_MVP), 1, GL_FALSE, &MVP[0][0]);

	//ToDo: mejorar
	int texturesLoaded = 0;
 	for (std::map<REEnums::TextureTypes, TTexture*>::iterator it = textures.begin(); it != textures.end(); ++it) {
		if (it->first == REEnums::TextureTypes::TEXTURE_AMBIENT) {
			glActiveTexture(GL_TEXTURE0 + texturesLoaded);
			glBindTexture(GL_TEXTURE_2D, it->second->getTextureID());
			glUniform1i(cache->getMatrixID(REEnums::Matrices::MATRIX_TEXTURE_AMBIENT), texturesLoaded);
		} else if (it->first == REEnums::TextureTypes::TEXTURE_DIFFUSE) {
			glActiveTexture(GL_TEXTURE0 + texturesLoaded);
			glBindTexture(GL_TEXTURE_2D, it->second->getTextureID());
			glUniform1i(cache->getMatrixID(REEnums::Matrices::MATRIX_TEXTURE_DIFFUSE), texturesLoaded);
		} else if (it->first == REEnums::TextureTypes::TEXTURE_SPECULAR) {
			glActiveTexture(GL_TEXTURE0 + texturesLoaded);
			glBindTexture(GL_TEXTURE_2D, it->second->getTextureID());
			glUniform1i(cache->getMatrixID(REEnums::Matrices::MATRIX_TEXTURE_SPECULAR), texturesLoaded);
		} else if (it->first == REEnums::TextureTypes::TEXTURE_ALPHA) {
			glActiveTexture(GL_TEXTURE0 + texturesLoaded);
			glBindTexture(GL_TEXTURE_2D, it->second->getTextureID());
			glUniform1i(cache->getMatrixID(REEnums::Matrices::MATRIX_TEXTURE_ALPHA), texturesLoaded);
		} else if (it->first == REEnums::TextureTypes::TEXTURE_BUMP) {
			glActiveTexture(GL_TEXTURE0 + texturesLoaded);
			glBindTexture(GL_TEXTURE_2D, it->second->getTextureID());
			glUniform1i(cache->getMatrixID(REEnums::Matrices::MATRIX_TEXTURE_BUMP), texturesLoaded);
		}
		texturesLoaded++;
	}

	glBindBuffer(GL_ARRAY_BUFFER, VBOID);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (3 + 3 + 2) * sizeof(f32), BUFFER_OFFSET(0));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (3 + 3 + 2) * sizeof(f32), BUFFER_OFFSET(3 * sizeof(f32)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, (3 + 3 + 2) * sizeof(f32), BUFFER_OFFSET((3 + 3) * sizeof(f32)));

	// Index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBOID);

	//glDrawArrays(GL_TRIANGLES, 0, mesh->getIndices().size());
	// Draw the triangles!
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

void TMesh::setTexture(REEnums::TextureTypes tt, TTexture* t){
	textures[tt] = t;
}

ResourceMesh* TMesh::getMesh(){
	return mesh;
}

ResourceMaterial* TMesh::getMaterial(){
	return material;
}