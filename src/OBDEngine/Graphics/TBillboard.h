#ifndef TBILLBOARD_H
#define TBILLBOARD_H

#include "TEntity.h"
#include "../OBDColor.h"

class TBillboard : public TEntity {
    
    public:
        TBillboard(GLuint, glm::vec3, glm::vec2);

        virtual ~TBillboard();

        void beginDraw();

        void endDraw();

        void setColor(OBDColor);

        void setFrontColor(OBDColor);

        void setPosition(glm::vec3);

        void setSize(glm::vec2);

		void setFrontWidth(f32);

        OBDColor getColor();

        OBDColor getFrontColor();

        glm::vec3 getPosition();

        glm::vec2 getSize();

        f32 getFrontWidth();

    private:
        glm::vec3 position;
		glm::vec2 size;
        glm::vec4 color;

		f32 frontWidth;
        glm::vec4 frontColor;
        
		GLuint VAO;
        GLuint VBO;

		GLuint CameraRight_worldspace_ID;
		GLuint CameraUp_worldspace_ID;
		GLuint ViewProjMatrixID;
		GLuint positionID;
		GLuint sizeID;
		GLuint colorID;
		GLuint frontWidthID;
		GLuint frontColorID;

};

#endif