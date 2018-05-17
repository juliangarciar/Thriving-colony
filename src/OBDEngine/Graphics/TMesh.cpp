#include "TMesh.h"

#define MAX_LIGHTS 10

TMesh::TMesh(glslMesh *r, OBDMaterial *m) : TEntity() {
	mesh = r;
	material = m;

	modelMatrix = glm::mat4(1.0f);

	// Generate a buffer for the vertices
	glGenBuffers(1, &VBOID);
	glBindBuffer(GL_ARRAY_BUFFER, VBOID);
	glBufferData(GL_ARRAY_BUFFER, mesh -> vbo.size() * sizeof(f32), &mesh -> vbo[0], GL_STATIC_DRAW);
	
	// Generate a buffer for the ibo as well
	glGenBuffers(1, &IBOID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBOID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh -> ibo.size() * sizeof(u32), &mesh -> ibo[0] , GL_STATIC_DRAW);

	// Lights
	glGenBuffers(1, &lightID);
	glBindBuffer(GL_UNIFORM_BUFFER, lightID);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(glslLight) * MAX_LIGHTS, 0, GL_DYNAMIC_DRAW);

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
	glDeleteBuffers(1, &VBOID);
	glDeleteBuffers(1, &IBOID);
}

void TMesh::beginDraw() { 
	glm::mat4 pM = *cache.getProjectionMatrix();
	glm::mat4 vM = *cache.getViewMatrix();
	modelMatrix = cache.getMatrixStack().top();

	// Matrices
	glm::mat4 MV = vM * modelMatrix;
	glm::mat4 MVP = pM * vM * modelMatrix;
	glUniformMatrix4fv(cache.getID(OBDEnums::OpenGLIDs::MATRIX_MODEL), 1, GL_FALSE, &modelMatrix[0][0]);
	glUniformMatrix4fv(cache.getID(OBDEnums::OpenGLIDs::MATRIX_VIEW), 1, GL_FALSE, &vM[0][0]);
	glUniformMatrix4fv(cache.getID(OBDEnums::OpenGLIDs::MATRIX_PROJECTION), 1, GL_FALSE, &pM[0][0]);
	glUniformMatrix4fv(cache.getID(OBDEnums::OpenGLIDs::MATRIX_MV), 1, GL_FALSE, &MV[0][0]);
	glUniformMatrix4fv(cache.getID(OBDEnums::OpenGLIDs::MATRIX_MVP), 1, GL_FALSE, &MVP[0][0]);

	// Camera
	glUniform3fv(cache.getID(OBDEnums::OpenGLIDs::CAMERA_POSITION), 1, &cache.getCameraPosition()[0]);

	//Send lights
	if (cache.getLights()->size()){   
		i32 lightNumber = cache.getLights()->size();
    	if (lightNumber > MAX_LIGHTS) lightNumber = MAX_LIGHTS;
		glUniform1i(cache.getID(OBDEnums::OpenGLIDs::LIGHT_AMOUNT), lightNumber);
		glBindBuffer(GL_UNIFORM_BUFFER, lightID);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glslLight) * cache.getLights()->size(), &cache.getLights()->at(0));
		glBindBufferBase(GL_UNIFORM_BUFFER, 1, lightID);
	}

	//Send material
	glBindBuffer(GL_UNIFORM_BUFFER, materialID);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glslMaterial), material->getGLSLMaterial()); // ¿?
	glBindBufferBase(GL_UNIFORM_BUFFER, 2, materialID);

	//Send textures
	glBindBuffer(GL_UNIFORM_BUFFER, textureID);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glslTexture), material->getGLSLActiveTextures()); //¿?
	glBindBufferBase(GL_UNIFORM_BUFFER, 3, textureID);

	i32 loadedTextures = 0;

	if (material->getGLSLActiveTextures()->diffuseTexture == 1){
		glActiveTexture(GL_TEXTURE0 + loadedTextures);
		glBindTexture(GL_TEXTURE_2D, material->getTexture(OBDEnums::TextureTypes::TEXTURE_DIFFUSE)->getTextureID());
		glUniform1i(cache.getID(OBDEnums::OpenGLIDs::SAMPLER_DIFFUSE), loadedTextures);
		loadedTextures++;
	}

	if (material->getGLSLActiveTextures()->oclusionsTexture == 1){
		glActiveTexture(GL_TEXTURE0 + loadedTextures);
		glBindTexture(GL_TEXTURE_2D, material->getTexture(OBDEnums::TextureTypes::TEXTURE_OCLUSIONS)->getTextureID());
		glUniform1i(cache.getID(OBDEnums::OpenGLIDs::SAMPLER_OCLUSIONS), loadedTextures);
		loadedTextures++;
	}

	if (material->getGLSLActiveTextures()->specularTexture == 1){
		glActiveTexture(GL_TEXTURE0 + loadedTextures);
		glBindTexture(GL_TEXTURE_2D, material->getTexture(OBDEnums::TextureTypes::TEXTURE_SPECULAR)->getTextureID());
		glUniform1i(cache.getID(OBDEnums::OpenGLIDs::SAMPLER_SPECULAR), loadedTextures);
		loadedTextures++;
	}

	if (material->getGLSLActiveTextures()->alphaTexture == 1){
		glActiveTexture(GL_TEXTURE0 + loadedTextures);
		glBindTexture(GL_TEXTURE_2D, material->getTexture(OBDEnums::TextureTypes::TEXTURE_ALPHA)->getTextureID());
		glUniform1i(cache.getID(OBDEnums::OpenGLIDs::SAMPLER_ALPHA), loadedTextures);
		loadedTextures++;
	}

	if (material->getGLSLActiveTextures()->bumpTexture == 1){
		glActiveTexture(GL_TEXTURE0 + loadedTextures);
		glBindTexture(GL_TEXTURE_2D, material->getTexture(OBDEnums::TextureTypes::TEXTURE_BUMP)->getTextureID());
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
		GL_TRIANGLES,			// mode
		mesh -> ibo.size(),	// count
		GL_UNSIGNED_INT,		// type
		(void*)0				// element array buffer offset
	);
}

void TMesh::endDraw() {
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

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void TMesh::setMaterial(OBDMaterial *m){
	material = m;
}

OBDMaterial *TMesh::getMaterial(){
	return material;
}