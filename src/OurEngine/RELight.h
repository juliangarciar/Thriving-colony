#ifndef RELIGHT_H
#define RELIGHT_H

#include <vector>
#include <algorithm>
#include <Types.h>
#include "TNode.h"
#include "TColor.h"
#include "TLight.h"
#include "TTransform.h"



class RELight {
    public:
        /**
         * @brief 
         * 
         * @param parent 
         */
        RELight(TNode* parent);

        /**
         * @brief 
         * 
         */
        ~RELight();

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
         * @param TColor 
         */
        void setIntensity(TColor);
        /**
         * @brief 
         * 
         * @return TColor 
         */
        TColor getIntensity();

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
         * @brief returns the position of this light
         * 
         */
        glm::vec4 getPosition();
        
        /**
         * @brief 
         * 
         * @return TNode* 
         */
        TNode* getLightNode();

    private:

        TNode* lightNode;
        TNode* rotationNode;
        TNode* translationNode;
        TNode* scaleNode;
        
};

#endif