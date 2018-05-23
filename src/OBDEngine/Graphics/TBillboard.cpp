#include "TBillboard.h"
#include "TShader.h"

TBillboard::TBillboard(GLuint programID, glm::vec3 p, glm::vec2 s) : TEntity() {
    position = p;
	size = s;

	frontWidth = 0;
    color = glm::vec4(0, 0, 0, 0);
    frontColor = glm::vec4(1, 1, 1, 1);

	CameraRight_worldspace_ID = glGetUniformLocation(programID, "CameraRight_worldspace");
	CameraUp_worldspace_ID = glGetUniformLocation(programID, "CameraUp_worldspace");
	ViewProjMatrixID = glGetUniformLocation(programID, "VP");
	positionID = glGetUniformLocation(programID, "position");
	sizeID = glGetUniformLocation(programID, "size");
	colorID = glGetUniformLocation(programID, "color");
	frontWidthID = glGetUniformLocation(programID, "frontWidth");
	frontColorID = glGetUniformLocation(programID, "frontColor");

	// The VBO containing the 4 vertices of the particles.
	static const GLfloat g_vertex_buffer_data[] = { 
		 -0.5f, -0.5f, 0.0f,
		  0.5f, -0.5f, 0.0f,
		 -0.5f,  0.5f, 0.0f,
		  0.5f,  0.5f, 0.0f,
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	// load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0,                  
        3,                  
        GL_FLOAT,           
        GL_FALSE,           
        0,                  
        (void*)0            
    );

    glGenBuffers(1, &VBO);

	glBindVertexArray(0);
}

TBillboard::~TBillboard() {
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &VAO);
}

void TBillboard::beginDraw() {
	glm::mat4 pM = *cache.getProjectionMatrix();
	glm::mat4 vM = *cache.getViewMatrix();

	glm::mat4 vpM = pM * vM;

	glUniform3f(CameraRight_worldspace_ID, vM[0][0], vM[1][0], vM[2][0]);
	glUniform3f(CameraUp_worldspace_ID, vM[0][1], vM[1][1], vM[2][1]);
	glUniformMatrix4fv(ViewProjMatrixID, 1, GL_FALSE, &vpM[0][0]);
	glUniform3f(positionID, position.x, position.y, position.z);
	glUniform2f(sizeID, size.x, size.y);
	glUniform4f(colorID, color.x, color.y, color.z, color.a);
	glUniform1f(frontWidthID, frontWidth);
	glUniform4f(frontColorID, frontColor.x, frontColor.y, frontColor.z, frontColor.a);

	glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}

void TBillboard::endDraw() {
	
}

void TBillboard::setPosition(glm::vec3 pos) {
    position = pos;
}

void TBillboard::setColor(OBDColor newColor) {
    color = newColor.getRGBA();
}

void TBillboard::setFrontColor(OBDColor newFrontColor) {
    frontColor = newFrontColor.getRGBA();
}

void TBillboard::setSize(glm::vec2 newSize) {
	size = newSize;
}

void TBillboard::setFrontWidth(f32 newFrontWidth) {
	frontWidth = newFrontWidth;
}

OBDColor TBillboard::getColor() {
    return OBDColor(color);
}

OBDColor TBillboard::getFrontColor() {
    return frontColor;
}

glm::vec3 TBillboard::getPosition() {
    return position;
}

glm::vec2 TBillboard::getSize() {
    return size;
}

f32 TBillboard::getFrontWidth() {
    return frontWidth;
}