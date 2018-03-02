#ifndef RECAMERA_H
#define RECAMERA_H

#include <vector>
#include <algorithm>
#include "../MathEngine/Vector3.h"
#include <Types.h>
#include "TNode.h"
#include "TCamera.h"
#include "TTransform.h"
#include "TEnums.h"
//#include "RamaEngine.h"


class RECamera {
    public:
        /**
         * @brief 
         * 
         * @param parent 
         */
        RECamera(TNode* parent);

        /**
         * @brief 
         * 
         */
        ~RECamera();

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
         * @param active 
         */
        void setActive(bool active);

        /**
         * @brief 
         * 
         * @param n 
         */
        void setNear(f32 n);

        /**
         * @brief 
         * 
         * @param f 
         */
        void setFar(f32 f);

        /**
         * @brief 
         * 
         * @param r 
         */
        void setRight(f32 r);

        /**
         * @brief 
         * 
         * @param l 
         */
        void setLeft(f32 l);

        /**
         * @brief 
         * 
         * @param t 
         */
        void setTop(f32 t);

        /**
         * @brief 
         * 
         * @param b 
         */
        void setBottom(f32 b);

        /**
         * @brief 
         * 
         * @param proj 
         */
        void setProjectionMode(TEnums::CameraProjection proj);

        /**
         * @brief 
         * 
         * @param fov 
         */
        void setFov(f32 fov);

        /**
          * @brief 
          * 
          * @param tX 
          * @param tY 
          * @param tZ 
          */
        void setTargetPosition(f32 tX, f32 tY, f32 tZ);

        // En realidad no se si se necesitan getters pero los pongo por si acaso

        /**
         * @brief 
         * 
         */
        bool getActive();

        /**
         * @brief 
         * 
         * @return f32 
         */
        f32 getNear();

        /**
         * @brief 
         * 
         * @return f32 
         */
        f32 getFar();

        /**
         * @brief 
         * 
         * @return f32 
         */
        f32 getRight();

        /**
         * @brief 
         * 
         * @return f32 
         */
        f32 getLeft();

        /**
         * @brief 
         * 
         * @return f32 
         */
        f32 getTop();

        /**
         * @brief 
         * 
         * @return f32 
         */
        f32 getBottom();

        /**
         * @brief 
         * 
         * @return TEnums::CameraProjection 
         */
        TEnums::CameraProjection getProjectionMode();

        /**
         * @brief 
         * 
         * @return f32 
         */
        f32 getFov();

        /**
         * @brief 
         * 
         * @return TNode* 
         */
        TNode* getCameraNode();
        

    private:

        TNode* cameraNode;
        TNode* rotationNode;
        TNode* translationNode;
        TNode* scaleNode;
        
};

#endif