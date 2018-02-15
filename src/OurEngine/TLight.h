#ifndef TLIGHT_H
#define TLIGHT_H

#include "TEntity.h"
#include "TColor.h"

class TLight : public TEntity {
    public:
        /**
         * @brief 
         * 
         */
        TLight();
        /**
         * @brief 
         * 
         */
        ~TLight();

        /**
         * @brief 
         * 
         */
        void beginDraw();
        /**
         * @brief 
         * 
         */
        void endDraw();
        

        /**
         * @brief 
         * 
         * @param TColor 
         */
        void setIntensity(TColor);
        /**
         * @brief 
         * 
         * @return TColor 
         */
        TColor getIntensity();
    private:
        TColor intensity;
};

#endif