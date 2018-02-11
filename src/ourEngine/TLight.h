#ifndef TLIGHT_H
#define TLIGHT_H

#include "TEntity.h"
#include "TColor.h"

class TLight : public TEntity {
    public:
        TLight();
        ~TLight();

        void beginDraw();
        void endDraw();
        
        void setIntensity(TColor);
        TColor getIntensity();
    private:
        TColor intensity;
};

#endif