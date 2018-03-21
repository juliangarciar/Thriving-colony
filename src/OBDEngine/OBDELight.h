#ifndef OBDELIGHT_H
#define OBDELIGHT_H

#include "OBDETypes.h"
#include "OBDEColor.h"
#include "Graphics/TNode.h"
#include "Graphics/TTransform.h"
#include "Graphics/TLight.h"

class OBDELight {
    public:
        /**
         * @brief 
         */
        OBDELight(OBDEColor color, u32 intensity);

        /**
         * @brief 
         * 
         * @param parent 
         */
        OBDELight(TNode* parent, OBDEColor color, u32 intensity);

        /**
         * @brief 
         * 
         */
        ~OBDELight();

        /**
         * @brief 
         * 
         * @param tX 
         * @param tY 
         * @param tZ 
         */
        void rotate(f32 rX, f32 rY, f32 rZ, f32 angle);

        /**
         * @brief 
         * 
         * @param sX 
         * @param sY 
         * @param sZ 
         */
        void scale(f32 sX, f32 sY, f32 sZ);

        /**
         * @brief 
         * 
         * @param tX 
         * @param tY 
         * @param tZ 
         */
        void translate(f32 tX, f32 tY, f32 tZ);

        /**
         * @brief 
         * 
         * @param OBDEColor 
         */
        void setColor(OBDEColor);
        
        /**
         * @brief 
         * 
         * @return OBDEColor 
         */
        OBDEColor getColor();
        
        /**
         * @brief 
         * 
         * @param OBDEColor 
         */
        void setIntensity(u32);

        /**
         * @brief 
         * 
         * @return OBDEColor 
         */
        u32 getIntensity();

        /**
         * @brief set the light to active or inactive
         * 
         * @param bool new light active state
         */
        void setActive(bool);

        /**
         * @brief returns wether or not the light is active
         * 
         * @return true if the light is active
         * @return false otherwise
         */
        bool getActive();
        
        /**
         * @brief 
         * 
         * @return TNode* 
         */
        TNode* getLightNode();
        
        /**
         * @brief 
         * 
         * @return TLight* 
         */
        TLight* getLightEntity();

    private:
        TNode* lightNode;
        TNode* rotationNode;
        TNode* translationNode;
        TNode* scaleNode;
};

#endif