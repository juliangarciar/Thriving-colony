#include "TMesh.h"

TMesh::TMesh(glslMesh *r, OBDMaterial *m) : TEntity() {
	mesh = r;
	material = m;

	modelMatrix = glm::mat4(1.0f);

	// Material
	glGenBuffers(1, &materialID);
	glBindBuffer(GL_UNIFORM_BUFFER, materialID);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(glslMaterial), material->getGLSLMaterial(), GL_DYNAMIC_DRAW); // ¿?
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glslMaterial), material->getGLSLMaterial()); // ¿?
	glBindBufferBase(GL_UNIFORM_BUFFER, 2, materialID);

	// Textures
	glGenBuffers(1, &textureID);
	glBindBuffer(GL_UNIFORM_BUFFER, textureID);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(glslTexture), material->getGLSLActiveTextures(), GL_DYNAMIC_DRAW); // ¿?
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glslTexture), material->getGLSLActiveTextures()); // ¿?
	glBindBufferBase(GL_UNIFORM_BUFFER, 3, textureID);
}

TMesh::~TMesh() {
	
}

void TMesh::beginDraw() { 
	// Fetch matrices
	glm::mat4 pM = *cache.getProjectionMatrix();
	glm::mat4 vM = *cache.getViewMatrix();
	modelMatrix = cache.getMatrixStack().top();

	// Multiply matrices 
	glm::mat4 MV = vM * modelMatrix;
	glm::mat4 MVP = pM * vM * modelMatrix;
	glUniformMatrix4fv(cache.getID(OBDEnums::OpenGLIDs::MATRIX_MODEL), 1, GL_FALSE, &modelMatrix[0][0]);
	glUniformMatrix4fv(cache.getID(OBDEnums::OpenGLIDs::MATRIX_VIEW), 1, GL_FALSE, &vM[0][0]);
	glUniformMatrix4fv(cache.getID(OBDEnums::OpenGLIDs::MATRIX_PROJECTION), 1, GL_FALSE, &pM[0][0]);
	glUniformMatrix4fv(cache.getID(OBDEnums::OpenGLIDs::MATRIX_MV), 1, GL_FALSE, &MV[0][0]);
	glUniformMatrix4fv(cache.getID(OBDEnums::OpenGLIDs::MATRIX_MVP), 1, GL_FALSE, &MVP[0][0]);

	// Camera
	glUniform3fv(cache.getID(OBDEnums::OpenGLIDs::CAMERA_POSITION), 1, &cache.getCameraPosition()[0]);

	//Send material
	glBindBuffer(GL_UNIFORM_BUFFER, materialID);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glslMaterial), material->getGLSLMaterial()); // ¿?
	glBindBufferBase(GL_UNIFORM_BUFFER, 2, materialID);

	//Send textures
	glBindBuffer(GL_UNIFORM_BUFFER, textureID);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glslTexture), material->getGLSLActiveTextures()); //¿?
	glBindBufferBase(GL_UNIFORM_BUFFER, 3, textureID);

	i32 loadedTextures = 0;
	/*
	* Send active textures if there are any.
	* Those that do exist, identify them.
	*/
	if (material->getGLSLActiveTextures()->diffuseTexture == 1) {
		glActiveTexture(GL_TEXTURE0 + loadedTextures);
		glBindTexture(GL_TEXTURE_2D, material->getTexture(OBDEnums::TextureTypes::TEXTURE_DIFFUSE)->getTexture()->getTextureID());
		glUniform1i(cache.getID(OBDEnums::OpenGLIDs::SAMPLER_DIFFUSE), loadedTextures);
		loadedTextures++;
	}

	if (material->getGLSLActiveTextures()->oclusionsTexture == 1) {
		glActiveTexture(GL_TEXTURE0 + loadedTextures);
		glBindTexture(GL_TEXTURE_2D, material->getTexture(OBDEnums::TextureTypes::TEXTURE_OCLUSIONS)->getTexture()->getTextureID());
		glUniform1i(cache.getID(OBDEnums::OpenGLIDs::SAMPLER_OCLUSIONS), loadedTextures);
		loadedTextures++;
	}

	if (material->getGLSLActiveTextures()->specularTexture == 1) {
		glActiveTexture(GL_TEXTURE0 + loadedTextures);
		glBindTexture(GL_TEXTURE_2D, material->getTexture(OBDEnums::TextureTypes::TEXTURE_SPECULAR)->getTexture()->getTextureID());
		glUniform1i(cache.getID(OBDEnums::OpenGLIDs::SAMPLER_SPECULAR), loadedTextures);
		loadedTextures++;
	}

	if (material->getGLSLActiveTextures()->alphaTexture == 1) {
		glActiveTexture(GL_TEXTURE0 + loadedTextures);
		glBindTexture(GL_TEXTURE_2D, material->getTexture(OBDEnums::TextureTypes::TEXTURE_ALPHA)->getTexture()->getTextureID());
		glUniform1i(cache.getID(OBDEnums::OpenGLIDs::SAMPLER_ALPHA), loadedTextures);
		loadedTextures++;
	}

	// Draw the triangles.
	glBindVertexArray(mesh->VAO);
	glDrawElements(GL_TRIANGLES, mesh->num_indices, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void TMesh::endDraw() {
	// Free textures off the buffers.
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void TMesh::setMaterial(OBDMaterial *m) {
	material = m;
}

OBDMaterial *TMesh::getMaterial() {
	return material;
}