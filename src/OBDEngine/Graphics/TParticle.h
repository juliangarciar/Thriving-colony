#ifndef TPARTICLE_H
#define TPARTICLE_H

#include "../OBDColor.h"

class TParticle {
    
    public:
        TParticle(OBDColor, OBDColor, i32, i32, glm::vec3, glm::vec3, glm::vec3, glm::vec2, glm::vec2);

        virtual ~TParticle();
        
        void setColor(OBDColor);
        void setStartColor(OBDColor);
        void setEndTime(i32);
        void setStartTime(i32);
        void setPosition(glm::vec3);
        void setStartDirection(glm::vec3);
        void setDirection(glm::vec3);
        void setSize(glm::vec2);
        void setStartSize(glm::vec2);

    private:
        OBDColor color;
        OBDColor startColor;

        i32 endTime;
        i32 startTime;
    
        glm::vec3 position;
        glm::vec3 startDirection;
        glm::vec3 direction;
        glm::vec2 size;
        glm::vec2 startSize;
};

#endif