#include "TBillboard.h"

TBillboard::TBillboard(glm::vec3 pos) : TEntity() {
    position = pos;
    height = 20;
    topWidth = 100;
    bottomWidth = 100;
}

TBillboard::~TBillboard() {

}

void TBillboard::beginDraw() {
    
    static const GLfloat g_vertex_buffer_data[] = {
        position.x - bottomWidth / 2, position.y + 100.0f, position.z,
        position.x - bottomWidth / 2, position.y + 100.0f + height, position.z,
        position.x + bottomWidth / 2, position.y + 100.0f + height, position.z,
        position.x - bottomWidth / 2, position.y + 100.0f, position.z,
        position.x + bottomWidth / 2, position.y + 100.0f, position.z,
        position.x + bottomWidth / 2, position.y + 100.0f + height, position.z,
    };
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
        0,                  // atributo 0. No hay razón particular para el 0, pero debe corresponder en el shader.
        3,                  // tamaño
        GL_FLOAT,           // tipo
        GL_FALSE,           // normalizado?
        0,                  // Paso
        (void*)0            // desfase del buffer
    );
    // Dibujar el triángulo
    glDrawArrays(GL_TRIANGLES, 0, 3); // Empezar desde el vértice 0S; 3 vértices en total -> 1 triángulo
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