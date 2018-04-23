#include "TMesh.h"

#include "../ResourceManager/ResourceOBJ.h"

#define MAX_LIGHTS 10

TMesh::TMesh(ResourceMesh r, ResourceMaterial m) : TEntity() {
	mesh = r;
	material = m;

	for (int i = 0; i < OBDEnums::TextureTypes::TEXTURE_SIZE; i++){
		textures.push_back(nullptr);
	}

	activeTextures.ambientTexture = false;
	activeTextures.diffuseTexture = false;
	activeTextures.specularTexture = false;
	activeTextures.alphaTexture = false;
	activeTextures.bumpTexture = false;
	
	currentMaterial.ambientColor = material.ambientColor;
	currentMaterial.diffuseColor = material.diffuseColor;
	currentMaterial.specularColor = material.specularColor;

	// Generate a buffer for the vertices
	std::cout << mesh.vbo.size() << std::endl;

	glGenBuffers(1, &VBOID);
	glBindBuffer(GL_ARRAY_BUFFER, VBOID);
	glBufferData(GL_ARRAY_BUFFER, mesh.vbo.size() * sizeof(f32), &mesh.vbo[0], GL_STATIC_DRAW);
	
	// Generate a buffer for the indices as well
	glGenBuffers(1, &IBOID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBOID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(us32), &mesh.indices[0] , GL_STATIC_DRAW);

	// Lights
	glGenBuffers(1, &lightID);
	glBindBuffer(GL_UNIFORM_BUFFER, lightID);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(glslLight) * MAX_LIGHTS, 0, GL_DYNAMIC_DRAW);

	// Material
	glGenBuffers(1, &materialID);
	glBindBuffer(GL_UNIFORM_BUFFER, materialID);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(glslMaterial), &currentMaterial, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glslMaterial), &currentMaterial);
	glBindBufferBase(GL_UNIFORM_BUFFER, 2, materialID);

	// Textures
	glGenBuffers(1, &textureID);
	glBindBuffer(GL_UNIFORM_BUFFER, textureID);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(glslTexture), &activeTextures, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glslTexture), &activeTextures);
	glBindBufferBase(GL_UNIFORM_BUFFER, 3, textureID);
}

TMesh::~TMesh() {
	glDeleteBuffers(1, &VBOID);
	glDeleteBuffers(1, &IBOID);
}

void TMesh::beginDraw() { 
	glm::mat4 pM = cache.getProjectionMatrix();
	glm::mat4 vM = cache.getViewMatrix();
	glm::mat4 mM = cache.getMatrixStack().top();

	// Matrices
	glm::mat4 MV = vM * mM;
	glm::mat4 MVP = pM * vM * mM;
	glUniformMatrix4fv(cache.getID(OBDEnums::OpenGLIDs::MATRIX_MODEL), 1, GL_FALSE, &mM[0][0]);
	glUniformMatrix4fv(cache.getID(OBDEnums::OpenGLIDs::MATRIX_VIEW), 1, GL_FALSE, &vM[0][0]);
	glUniformMatrix4fv(cache.getID(OBDEnums::OpenGLIDs::MATRIX_PROJECTION), 1, GL_FALSE, &pM[0][0]);
	glUniformMatrix4fv(cache.getID(OBDEnums::OpenGLIDs::MATRIX_MV), 1, GL_FALSE, &MV[0][0]);
	glUniformMatrix4fv(cache.getID(OBDEnums::OpenGLIDs::MATRIX_MVP), 1, GL_FALSE, &MVP[0][0]);

	//Send lights
	glUniform1i(cache.getID(OBDEnums::OpenGLIDs::LIGHT_AMOUNT), cache.getLights()->size());
	glBindBuffer(GL_UNIFORM_BUFFER, lightID);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glslLight) * cache.getLights()->size(), &cache.getLights()->at(0));
	glBindBufferBase(GL_UNIFORM_BUFFER, 1, lightID);

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
		mesh.indices.size(),    // count
		GL_UNSIGNED_SHORT,   // type
		(void*)0           // element array buffer offset
	);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void TMesh::endDraw() {

}

void TMesh::setMaterial(ResourceMaterial m){
	material = m;
	
	currentMaterial.ambientColor = material.ambientColor;
	currentMaterial.diffuseColor = material.diffuseColor;
	currentMaterial.specularColor = material.specularColor;

	//Send material
	glBindBuffer(GL_UNIFORM_BUFFER, materialID);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glslMaterial), &currentMaterial);
	glBindBufferBase(GL_UNIFORM_BUFFER, 2, materialID);
}

void TMesh::setTexture(OBDEnums::TextureTypes tt, TTexture* t){
	if (textures[(int)tt] != nullptr) delete textures[(int)tt];
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

	//Send textures
	glBindBuffer(GL_UNIFORM_BUFFER, textureID);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glslTexture), &activeTextures);
	glBindBufferBase(GL_UNIFORM_BUFFER, 3, textureID);
}

ResourceMesh TMesh::getMesh(){
	return mesh;
}

ResourceMaterial TMesh::getMaterial(){
	return material;
}