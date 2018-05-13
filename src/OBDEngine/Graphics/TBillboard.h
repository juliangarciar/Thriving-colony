#ifndef TBILLBOARD_H
#define TBILLBOARD_H

#include "TEntity.h"
#include "../OBDColor.h"

class TBillboard : public TEntity {
    
    public:
        TBillboard(glm::vec3, GLuint);

        ~TBillboard();

        void beginDraw();

        void endDraw();

        void setColor(OBDColor*, OBDColor*);

        void setPosition(glm::vec3);

        void setSize(f32, f32, f32);

        OBDColor* getTopColor();

        OBDColor* getBottomColor();

        glm::vec3 getPosition();

        f32 getHeight();

        f32 getTopWidth();

        f32 getBottomWidth();

    private:
        glm::vec3 position;

        GLuint vertexbuffer;
        GLuint program;

        OBDColor* topColor;
        OBDColor* bottomColor;
        
        f32 height;
        f32 topWidth;
        f32 bottomWidth;
};

#endif