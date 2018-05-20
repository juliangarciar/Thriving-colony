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

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_DYNAMIC_DRAW);
}

TBillboard::~TBillboard() {
	glDeleteBuffers(1, &vertexbuffer);
}

void TBillboard::beginDraw() {
	glm::mat4 pM = *cache.getProjectionMatrix();
	glm::mat4 vM = *cache.getViewMatrix();

	glm::mat4 vpM = pM * vM;

	/*
	glm::vec3 vertexPosition_worldspace =
    position
    + glm::vec3(vM[0][0], vM[1][0], vM[2][0]) * 0.5f * size.x
    + glm::vec3(vM[0][1], vM[1][1], vM[2][1]) * 0.5f * size.y;

	std::cout << "Before = " << vertexPosition_worldspace.x << " " << vertexPosition_worldspace.y << " " << vertexPosition_worldspace.z << std::endl;

	glm::vec3 vertexPosition_screenspace = glm::project(vertexPosition_worldspace, vM, pM, glm::vec4(0,0,1280,720));

	std::cout << "After  = " << vertexPosition_screenspace.x << " " << vertexPosition_screenspace.y << " " << vertexPosition_screenspace.z << std::endl << std::endl;
	*/
	//ToDo: la componente z en screenSpace es mayor a 1 y eso hace que no salga
	
	glUniform3f(CameraRight_worldspace_ID, vM[0][0], vM[1][0], vM[2][0]);
	glUniform3f(CameraUp_worldspace_ID, vM[0][1], vM[1][1], vM[2][1]);
	glUniformMatrix4fv(ViewProjMatrixID, 1, GL_FALSE, &vpM[0][0]);
	glUniform3f(positionID, position.x, position.y, position.z);
	glUniform2f(sizeID, size.x, size.y);
	glUniform4f(colorID, color.x, color.y, color.z, color.a);
	glUniform1f(frontWidthID, frontWidth);
	glUniform4f(frontColorID, frontColor.x, frontColor.y, frontColor.z, frontColor.a);

    glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
        0,                  
        3,                  
        GL_FLOAT,           
        GL_FALSE,           
        0,                  
        (void*)0            
    );
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void TBillboard::endDraw() {
    glDisableVertexAttribArray(0);
}

void TBillboard::setPosition(glm::vec3 pos) {
    position = pos;
}

void TBillboard::setColor(OBDColor newColor, OBDColor newFrontColor) {
    color = newColor.getRGBA();
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