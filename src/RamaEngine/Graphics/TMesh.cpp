#include "TMesh.h"

#include "../ResourceManager/ResourceOBJ.h"

TMesh::TMesh(ResourceMesh *r, ResourceMaterial *m) : TEntity() {
	mesh = r;
	material = m;

	for (int i = 0; i < REEnums::TextureTypes::TEXTURE_SIZE; i++){
		textures.push_back(NULL);
	}

	activeTextures.ambientTexture = false;
	activeTextures.diffureTexture = false;
	activeTextures.specularTexture = false;
	activeTextures.alphaTexture = false;
	activeTextures.bumpTexture = false;

	// Generate a buffer for the vertices
	glGenBuffers(1, &VBOID);
	glBindBuffer(GL_ARRAY_BUFFER, VBOID);
	glBufferData(GL_ARRAY_BUFFER, mesh->getVBO().size() * sizeof(f32), &mesh->getVBO()[0], GL_STATIC_DRAW);
	
	// Generate a buffer for the indices as well
	glGenBuffers(1, &IBOID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBOID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->getIndices().size() * sizeof(us32), &mesh->getIndices()[0] , GL_STATIC_DRAW);

	// Material
	Material mat;
	mat.ambientColor = material->getAmbientColor();
	mat.diffuseColor = material->getDiffuseColor();
	mat.specularColor = material->getSpecularColor();
	glGenBuffers(1, &materialID);
	glBindBuffer(GL_UNIFORM_BUFFER, materialID);
	glBufferData(GL_UNIFORM_BUFFER , sizeof(Material), &mat, GL_STATIC_DRAW);

	// Textures
	glGenBuffers(1, &textureID);
	glBindBuffer(GL_UNIFORM_BUFFER, textureID);
	glBufferData(GL_UNIFORM_BUFFER , sizeof(Texture), &activeTextures, GL_STATIC_DRAW);

	// Lights
	glGenBuffers(1, &lightID);
	glBindBuffer(GL_UNIFORM_BUFFER, lightID);
	glBufferData(GL_UNIFORM_BUFFER , sizeof(Light) * cache.getLights()->size(), &cache.getLights()->at(0), GL_STATIC_DRAW);
}

TMesh::~TMesh() {
	glDeleteBuffers(1, &VBOID);
	glDeleteBuffers(1, &IBOID);
}

void TMesh::beginDraw() {    
	glm::mat4 pM = cache.getProjectionMatrix();
	glm::mat4 vM = cache.getViewMatrix();
	glm::mat4 mM = cache.getModelMatrix();

	// Matrices
	glm::mat4 MV = vM * mM;
	glm::mat4 MVP = pM * vM * mM;
	glUniformMatrix4fv(cache.getParamID(REEnums::ShaderParams::MATRIX_MODEL), 1, GL_FALSE, &mM[0][0]);
	glUniformMatrix4fv(cache.getParamID(REEnums::ShaderParams::MATRIX_VIEW), 1, GL_FALSE, &vM[0][0]);
	glUniformMatrix4fv(cache.getParamID(REEnums::ShaderParams::MATRIX_PROJECTION), 1, GL_FALSE, &pM[0][0]);
	glUniformMatrix4fv(cache.getParamID(REEnums::ShaderParams::MATRIX_MV), 1, GL_FALSE, &MV[0][0]);
	glUniformMatrix4fv(cache.getParamID(REEnums::ShaderParams::MATRIX_MVP), 1, GL_FALSE, &MVP[0][0]);
	glUniformBlockBinding(cache.getCurrentProgramID(), cache.getParamID(REEnums::ShaderParams::BUFFER_MATERIAL), materialID);
	glUniformBlockBinding(cache.getCurrentProgramID(), cache.getParamID(REEnums::ShaderParams::BUFFER_TEXTURE), textureID);
	glUniformBlockBinding(cache.getCurrentProgramID(), cache.getParamID(REEnums::ShaderParams::BUFFER_LIGHT), lightID);

	//ToDo: mejorar
	int i = 0;
	for (int i = 0; i < REEnums::TextureTypes::TEXTURE_SIZE; i++){
		if (textures[i] != NULL){
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, textures[i]->getTextureID());
			i++;
		}
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

//ToDo: mejorar
void TMesh::setTexture(REEnums::TextureTypes tt, TTexture* t){
	textures[(int)tt] = t;
	switch(tt){
		case REEnums::TextureTypes::TEXTURE_AMBIENT:
			activeTextures.ambientTexture = true;
		break;
		case REEnums::TextureTypes::TEXTURE_DIFFUSE:
			activeTextures.diffureTexture = true;
		break;
		case REEnums::TextureTypes::TEXTURE_SPECULAR:
			activeTextures.specularTexture = true;
		break;
		case REEnums::TextureTypes::TEXTURE_ALPHA:
			activeTextures.alphaTexture = true;
		break;
		case REEnums::TextureTypes::TEXTURE_BUMP:
			activeTextures.bumpTexture = true;
		break;
	}
}

ResourceMesh* TMesh::getMesh(){
	return mesh;
}

ResourceMaterial* TMesh::getMaterial(){
	return material;
}