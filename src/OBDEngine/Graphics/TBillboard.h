#ifndef TBILLBOARD_H
#define TBILLBOARD_H

#include <GL/glew.h>

#include "TEntity.h"

class TBillboard : public TEntity {
    public:
        TBillboard(f32, f32, f32);

        ~TBillboard();

        void beginDraw();

    private:
        glm::vec3 worldPosition;
        GLuint vertexbuffer;
};

#endif