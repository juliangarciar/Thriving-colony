#include "TBillboard.h"
#include "TShader.h"

TBillboard::TBillboard(glm::vec3 pos, GLuint shader) : TEntity() {
    position = pos;
    height = 2;
    topWidth = 5;
    bottomWidth = 10;

    program = shader;
    
    bottomColor = new OBDColor(255, 255, 255);
    topColor = new OBDColor();
}

TBillboard::~TBillboard() {
    delete bottomColor;
    delete topColor;
}

void TBillboard::beginDraw() {
    static const GLfloat g_vertex_buffer_data[] = {
        position.x - bottomWidth / 2, position.y + 0.0f, position.z,
        position.x + bottomWidth / 2, position.y + 0.0f + height, position.z,
        position.x - bottomWidth / 2, position.y + 0.0f + height, position.z,
        position.x - bottomWidth / 2, position.y + 0.0f, position.z,
        position.x + bottomWidth / 2, position.y + 0.0f, position.z,
        position.x + bottomWidth / 2, position.y + 0.0f + height, position.z,
        
        position.x - bottomWidth / 2, position.y + 0.0f, position.z,
        position.x + topWidth / 2, position.y + 0.0f + height, position.z,
        position.x - bottomWidth / 2, position.y + 0.0f + height, position.z,
        position.x - bottomWidth / 2, position.y + 0.0f, position.z,
        position.x + topWidth / 2, position.y + 0.0f, position.z,
        position.x + topWidth / 2, position.y + 0.0f + height, position.z
    };

    glm::vec3 _color = glm::vec3(1,0,1);
    GLuint colorID = glGetUniformLocation(program, "color");
    glUniform3f(colorID, 1, GL_FALSE, _color[0]);
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0,                  
        3,                  
        GL_FLOAT,           
        GL_FALSE,           
        0,                  
        (void*)0            
    );

    // Dibujar el triángulo
    glDrawArrays(GL_TRIANGLES, 0, 12); // Empezar desde el vértice 0; 12 vértices en total -> 1 triángulo
    glDisableVertexAttribArray(0);
}

void TBillboard::endDraw() {

}

void TBillboard::setPosition(glm::vec3 pos) {
    position = pos;
}

void TBillboard::setColor(OBDColor* newTopColor, OBDColor* newBottomColor) {
    if (newTopColor != nullptr) {
        topColor = newTopColor;
    }

    if (newBottomColor != nullptr) {
        bottomColor = newBottomColor;
    }
}

void TBillboard::setSize(f32 newHeight, f32 newTopWidth, f32 newBottomWidth) {
    if (newHeight != -1) {
        height = newHeight;
    }

    topWidth = newTopWidth;

    if (newBottomWidth != -1) {
        bottomWidth = newBottomWidth;
    }
}

OBDColor* TBillboard::getTopColor() {
    return topColor;
}

OBDColor* TBillboard::getBottomColor() {
    return bottomColor;
}

glm::vec3 TBillboard::getPosition() {
    return position;
}

f32 TBillboard::getHeight() {
    return height;
}

f32 TBillboard::getTopWidth() {
    return topWidth;
}

f32 TBillboard::getBottomWidth() {
    return bottomWidth;
}