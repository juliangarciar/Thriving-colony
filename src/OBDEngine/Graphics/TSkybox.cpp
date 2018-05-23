#include "TSkybox.h"

TSkybox::TSkybox(GLuint p, TCubemapTexture* t) : TEntity() {
	texture = t;
	programID = p;

    GLfloat cube_vertices[24] = {
		-1.0,  	-1.0,	-1.0,
		1.0, 	-1.0,	-1.0,
		1.0, 	1.0,	-1.0,
		-1.0,  	1.0,	-1.0,
		-1.0,	-1.0,	1.0,
		1.0,	-1.0,	1.0,
		1.0,	1.0,	1.0,
		-1.0,	1.0,	1.0,
    };

    GLushort cube_indices[36] = {    
		0, 1, 3, 
		3, 1, 2,
		1, 5, 2, 
		2, 5, 6,
		5, 4, 6, 
		6, 4, 7,
		4, 0, 7, 
		7, 0, 3,
		3, 2, 7, 
		7, 2, 6,
		4, 5, 0, 
		0, 5, 1
    };

	glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &vbo_cube_vertices);
    glGenBuffers(1, &ibo_cube_indices);

	glBindVertexArray(VAO);

	// load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_vertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

	// load data into index buffers
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_cube_indices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), 0);
	
	glBindVertexArray(0);

	vpID = glGetUniformLocation(programID, "VP");
	skyboxID = glGetUniformLocation(programID, "skybox");
}

TSkybox::~TSkybox() {

}

void TSkybox::beginDraw() {
	glDepthMask(GL_FALSE);
	glDepthFunc(GL_LEQUAL);

	glm::mat4 pM = *cache.getProjectionMatrix();
	glm::mat4 vM = glm::mat4(glm::mat3(*cache.getViewMatrix()));

	glm::mat4 vpM = pM * vM;

	glUniformMatrix4fv(vpID, 1, GL_FALSE, glm::value_ptr(vpM));

	//Texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture->getTextureID());
	glUniform1i(skyboxID, 0);

	// Draw the triangles!
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
}

void TSkybox::endDraw() {
	glDisableVertexAttribArray(0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);
}

void TSkybox::setTexture(TCubemapTexture* t) {
    texture = t;
}
