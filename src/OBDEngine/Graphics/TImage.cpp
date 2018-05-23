#include "TImage.h"

TImage::TImage(GLuint pID, ResourceIMG *d){	
	programID = pID;
	data = d;

	float quad[20] = {
		-1.0f,  1.0f, 0.0f, 0.0f, 0.0f,
		-1.0f, -1.0f, 0.0f, 0.0f, 1.0f,
		 1.0f, -1.0f, 0.0f, 1.0f, 1.0f,
		 1.0f,  1.0f, 0.0f, 1.0f, 0.0f
	};
	
	unsigned short elem[6] = {
		0, 1, 2,
		0, 2, 3
	};

	glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &vert_buf);
    glGenBuffers(1, &elem_buf);

	glBindVertexArray(VAO);

	// load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, vert_buf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);

	// load data into index buffers
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elem_buf);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elem), elem, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (3 + 2) * sizeof(f32), BUFFER_OFFSET(0));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, (3 + 2) * sizeof(f32), BUFFER_OFFSET(3 * sizeof(f32)));
	
	glBindVertexArray(0);

	mvpID = glGetUniformLocation(programID, "MVP");
	textureID = glGetUniformLocation(programID, "videoTexture");

	mvp = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
}

TImage::~TImage(){
	glDeleteBuffers(1, &vert_buf);
	glDeleteBuffers(1, &uv_buf);
	glDeleteBuffers(1, &elem_buf);
}

void TImage::beginDraw(){
	glUniformMatrix4fv(mvpID, 1, GL_FALSE, glm::value_ptr(mvp));

	//Texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, data->getTextureID());
	glUniform1i(textureID, 0);

	// Draw the triangles!
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
}

void TImage::endDraw(){
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}