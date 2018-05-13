#include "TSkybox.h"

TSkybox::TSkybox(TTexture* texture) : TEntity() {
    setTexture(texture);
}

TSkybox::~TSkybox() {
}

void TSkybox::beginDraw() {
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    GLfloat cube_vertices[] = {
  -1.0,  1.0,  1.0,
  -1.0, -1.0,  1.0,
   1.0, -1.0,  1.0,
   1.0,  1.0,  1.0,
  -1.0,  1.0, -1.0,
  -1.0, -1.0, -1.0,
   1.0, -1.0, -1.0,
   1.0,  1.0, -1.0,
    };
    GLuint vbo_cube_vertices;
    glGenBuffers(1, &vbo_cube_vertices);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_vertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);
    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    // cube indices for index buffer object
    GLushort cube_indices[] = {
    0, 1, 2, 3,
    3, 2, 6, 7,
    7, 6, 5, 4,
    4, 5, 1, 0,
    0, 3, 7, 4,
    1, 2, 6, 5,
    };
    GLuint ibo_cube_indices;
    glGenBuffers(1, &ibo_cube_indices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_cube_indices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);

    glDrawElements(GL_QUADS, sizeof(cube_indices)/sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
}

void TSkybox::endDraw() {

}

void TSkybox::setTexture(TTexture* texture) {
    textureID = texture->getTextureID();
}
