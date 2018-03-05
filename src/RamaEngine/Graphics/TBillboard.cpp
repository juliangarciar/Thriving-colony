#include "TBillboard.h"

TBillboard::TBillboard(f32 x, f32 y, f32 z) : TEntity() {
    glm::vec3 BillboardPos_worldspace(x, y, z);
    worldPosition = BillboardPos_worldspace;
}

TBillboard::~TBillboard() {

}

void TBillboard::beginDraw() {
    /*
    // Un arreglo de 3 vectores que representan 3 vértices
static const GLfloat g_vertex_buffer_data[] = {
   -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
};
    // Generar un buffer, poner el resultado en el vertexbuffer que acabamos de crear
    glGenBuffers(1, &vertexbuffer);
    // Los siguientes comandos le darán características especiales al 'vertexbuffer' 
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    // Darle nuestros vértices a  OpenGL.
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
/*
	glBegin(GL_LINE_LOOP);
	glVertex3f(worldPosition.x, worldPosition.y, worldPosition.z);
    glVertex3f(worldPosition.x, worldPosition.y, worldPosition.z);
    glVertex3f(worldPosition.x, worldPosition.y, worldPosition.z);
    glVertex3f(worldPosition.x, worldPosition.y, worldPosition.z);
	glEnd();
    */
}