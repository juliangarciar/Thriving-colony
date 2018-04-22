#ifndef TBILLBOARD_H
#define TBILLBOARD_H

#include <GL/glew.h>

#include "TEntity.h"
#include "../OBDColor.h"

class TBillboard : public TEntity {
    public:
        TBillboard(f32, f32, f32);

        ~TBillboard();

        void beginDraw();

        void endDraw();

        void setColor(OBDColor*, OBDColor*);

    private:
        glm::vec3 worldPosition;
        GLuint vertexbuffer;
        OBDColor* topColor;
        OBDColor* bottomColor;
};

#endif