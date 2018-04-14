#include "TMesh.h"

#include "../ResourceManager/ResourceOBJ.h"

TMesh::TMesh(ResourceMesh *r, ResourceMaterial *m) : TEntity() {
	mesh = r;
	material = m;

	for (int i = 0; i < OBDEnums::TextureTypes::TEXTURE_SIZE; i++){
		textures.push_back(NULL);
	}

	activeTextures.ambientTexture = false;
	activeTextures.diffuseTexture = false;
	activeTextures.specularTexture = false;
	activeTextures.alphaTexture = false;
	activeTextures.bumpTexture = false;
	
	currentMaterial.ambientColor = material->getAmbientColor();
	currentMaterial.diffuseColor = material->getDiffuseColor();
	currentMaterial.specularColor = material->getSpecularColor();

	// Generate a buffer for the vertices
	glGenBuffers(1, &VBOID);
	glBindBuffer(GL_ARRAY_BUFFER, VBOID);
	glBufferData(GL_ARRAY_BUFFER, mesh->getVBO().size() * sizeof(f32), &mesh->getVBO()[0], GL_STATIC_DRAW);
	
	// Generate a buffer for the indices as well
	glGenBuffers(1, &IBOID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBOID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->getIndices().size() * sizeof(us32), &mesh->getIndices()[0] , GL_STATIC_DRAW);

	std::cout << cache.getLights()->at(0).ambientComponent.r << " " << cache.getLights()->at(0).ambientComponent.g << " " << cache.getLights()->at(0).ambientComponent.b << std::endl; 

	// Lights
	glGenBuffers(1, &lightID);
	glBindBuffer(GL_UNIFORM_BUFFER, lightID);
	glBindBufferBase(GL_UNIFORM_BUFFER, 1, lightID);
	glNamedBufferData(lightID, sizeof(glslLight) * cache.getLights()->size(), nullptr, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glslLight) * cache.getLights()->size(), &cache.getLights()->at(0));
	glBindBufferRange(GL_UNIFORM_BUFFER, cache.getID(OBDEnums::OpenGLIDs::BUFFER_LIGHT), lightID, 0, sizeof(glslLight) * cache.getLights()->size());

	// Material
	glGenBuffers(1, &materialID);
	glBindBuffer(GL_UNIFORM_BUFFER, materialID);
	glBindBufferBase(GL_UNIFORM_BUFFER, 2, materialID);
	glNamedBufferData(materialID, sizeof(glslMaterial), nullptr, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glslMaterial), &currentMaterial);
	glBindBufferRange(GL_UNIFORM_BUFFER, cache.getID(OBDEnums::OpenGLIDs::BUFFER_MATERIAL), materialID, 0, sizeof(glslMaterial));

	// Textures
	glGenBuffers(1, &textureID);
	glBindBuffer(GL_UNIFORM_BUFFER, textureID);
	glBindBufferBase(GL_UNIFORM_BUFFER, 3, textureID);
	glNamedBufferData(textureID, sizeof(glslTexture), nullptr, GL_DYNAMIC_DRAW);
}

TMesh::~TMesh() {
	glDeleteBuffers(1, &VBOID);
	glDeleteBuffers(1, &IBOID);
}

void TMesh::beginDraw() { 
	if (!active) return;
	   
	glm::mat4 pM = cache.getProjectionMatrix();
	glm::mat4 vM = cache.getViewMatrix();
	glm::mat4 mM = cache.getModelMatrix();

	// Matrices
	glm::mat4 MV = vM * mM;
	glm::mat4 MVP = pM * vM * mM;
	glUniformMatrix4fv(cache.getID(OBDEnums::OpenGLIDs::MATRIX_MODEL), 1, GL_FALSE, &mM[0][0]);
	glUniformMatrix4fv(cache.getID(OBDEnums::OpenGLIDs::MATRIX_VIEW), 1, GL_FALSE, &vM[0][0]);
	glUniformMatrix4fv(cache.getID(OBDEnums::OpenGLIDs::MATRIX_PROJECTION), 1, GL_FALSE, &pM[0][0]);
	glUniformMatrix4fv(cache.getID(OBDEnums::OpenGLIDs::MATRIX_MV), 1, GL_FALSE, &MV[0][0]);
	glUniformMatrix4fv(cache.getID(OBDEnums::OpenGLIDs::MATRIX_MVP), 1, GL_FALSE, &MVP[0][0]);

	// 

	int loadedTextures = 0;

	if (activeTextures.ambientTexture){
		glActiveTexture(GL_TEXTURE0 + loadedTextures);
		glBindTexture(GL_TEXTURE_2D, textures[OBDEnums::TextureTypes::TEXTURE_AMBIENT]->getTextureID());
		glUniform1i(cache.getID(OBDEnums::OpenGLIDs::SAMPLER_AMBIENT), loadedTextures);
		loadedTextures++;
	}

	if (activeTextures.diffuseTexture){
		glActiveTexture(GL_TEXTURE0 + loadedTextures);
		glBindTexture(GL_TEXTURE_2D, textures[OBDEnums::TextureTypes::TEXTURE_DIFFUSE]->getTextureID());
		glUniform1i(cache.getID(OBDEnums::OpenGLIDs::SAMPLER_DIFFUSE), loadedTextures);
		loadedTextures++;
	}

	if (activeTextures.specularTexture){
		glActiveTexture(GL_TEXTURE0 + loadedTextures);
		glBindTexture(GL_TEXTURE_2D, textures[OBDEnums::TextureTypes::TEXTURE_SPECULAR]->getTextureID());
		glUniform1i(cache.getID(OBDEnums::OpenGLIDs::SAMPLER_SPECULAR), loadedTextures);
		loadedTextures++;
	}

	if (activeTextures.alphaTexture){
		glActiveTexture(GL_TEXTURE0 + loadedTextures);
		glBindTexture(GL_TEXTURE_2D, textures[OBDEnums::TextureTypes::TEXTURE_ALPHA]->getTextureID());
		glUniform1i(cache.getID(OBDEnums::OpenGLIDs::SAMPLER_ALPHA), loadedTextures);
		loadedTextures++;
	}

	if (activeTextures.bumpTexture){
		glActiveTexture(GL_TEXTURE0 + loadedTextures);
		glBindTexture(GL_TEXTURE_2D, textures[OBDEnums::TextureTypes::TEXTURE_BUMP]->getTextureID());
		glUniform1i(cache.getID(OBDEnums::OpenGLIDs::SAMPLER_BUMP), loadedTextures);
		loadedTextures++;
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

void TMesh::setTexture(OBDEnums::TextureTypes tt, TTexture* t){
	textures[(int)tt] = t;
	switch(tt){
		case OBDEnums::TextureTypes::TEXTURE_AMBIENT:
			activeTextures.ambientTexture = true;
		break;
		case OBDEnums::TextureTypes::TEXTURE_DIFFUSE:
			activeTextures.diffuseTexture = true;
		break;
		case OBDEnums::TextureTypes::TEXTURE_SPECULAR:
			activeTextures.specularTexture = true;
		break;
		case OBDEnums::TextureTypes::TEXTURE_ALPHA:
			activeTextures.alphaTexture = true;
		break;
		case OBDEnums::TextureTypes::TEXTURE_BUMP:
			activeTextures.bumpTexture = true;
		break;
		default: break;
	}

	glBindBuffer(GL_UNIFORM_BUFFER, textureID);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glslTexture), &activeTextures);
	glBindBufferRange(GL_UNIFORM_BUFFER, cache.getID(OBDEnums::OpenGLIDs::BUFFER_TEXTURE), textureID, 0, sizeof(glslTexture));
}

ResourceMesh* TMesh::getMesh(){
	return mesh;
}

ResourceMaterial* TMesh::getMaterial(){
	return material;
}

void TMesh::setActive(bool a) {
	active = a;
}

bool TMesh::getActive() {
	return active;
}

void TMesh::setName(std::string n) {
	name = n;
}

std::string TMesh::getName() {
	return name;
}

void TMesh::setID(GLuint i) {
	ID = i;
}

GLuint TMesh::getID() {
	return ID;
}
