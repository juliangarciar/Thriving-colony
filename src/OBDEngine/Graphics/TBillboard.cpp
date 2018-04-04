#include "TBillboard.h"

TBillboard::TBillboard(f32 x, f32 y, f32 z) : TEntity() {
    glm::vec3 BillboardPos_worldspace(x, y, z);
    worldPosition = BillboardPos_worldspace;
}

TBillboard::~TBillboard() {

}

void TBillboard::beginDraw() {
    
    static const GLfloat g_vertex_buffer_data[] = {
        worldPosition.x - 100.0f, worldPosition.y + 100.0f, worldPosition.z,
        worldPosition.x - 100.0f, worldPosition.y + 120.0f, worldPosition.z,
        worldPosition.x + 100.0f, worldPosition.y + 120.0f, worldPosition.z,
        worldPosition.x - 100.0f, worldPosition.y + 100.0f, worldPosition.z,
        worldPosition.x + 100.0f, worldPosition.y + 100.0f, worldPosition.z,
        worldPosition.x + 100.0f, worldPosition.y + 120.0f, worldPosition.z,
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
        0,                    // Paso
        (void*)0            // desfase del buffer
    );
    // Dibujar el triángulo !
    glDrawArrays(GL_TRIANGLES, 0, 3); // Empezar desde el vértice 0S; 3 vértices en total -> 1 triángulo
    glDisableVertexAttribArray(0);
}