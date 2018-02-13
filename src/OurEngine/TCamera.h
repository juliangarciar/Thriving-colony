#ifndef TCAMERA_H
#define TCAMERA_H

#include "TEntity.h"

class TCamera : public TEntity {
    public:
        /**
         * @brief 
         * 
         * @param TEnums::CameraProjection 
         * @param f32 
         * @param f32 
         * @param f32 
         * @param f32 
         * @param f32 
         * @param f32 
         */
        TCamera(TEnums::CameraProjection, f32, f32, f32, f32, f32, f32);

        /**
         * @brief 
         * 
         */
        ~TCamera();


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
         * @param f32 
         * @param f32 
         * @param f32 
         * @param f32 
         * @param f32 
         * @param f32 
         */
        void setPerspective(f32, f32, f32, f32, f32, f32);

        /**
         * @brief 
         * 
         * @param f32 
         * @param f32 
         * @param f32 
         * @param f32 
         * @param f32 
         * @param f32 
         */
        void setParallel(f32, f32, f32, f32, f32, f32);

        /**
         * @brief 
         * 
         * @param TEnums::CameraProjection 
         */
        void setProjection(TEnums::CameraProjection);

        /**
         * @brief 
         * 
         * @param f32 
         */
        void setNear(f32);

        /**
         * @brief 
         * 
         * @param f32 
         */
        void setFar(f32);

        /**
         * @brief 
         * 
         * @param f32 
         */
        void setTop(f32);

        /**
         * @brief 
         * 
         * @param f32 
         */
        void setBottom(f32);

        /**
         * @brief 
         * 
         * @param f32 
         */
        void setLeft(f32);

        /**
         * @brief 
         * 
         * @param f32 
         */
        void setRight(f32);

        /**
         * @brief 
         * 
         * @return TEnums::CameraProjection 
         */
        TEnums::CameraProjection getProjection();

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
         * @return f32 
         */
        f32 getLeft();

        /**
         * @brief 
         * 
         * @return f32 
         */
        f32 getRight();
    private:
        //ToDo: proyeccion GLM
        TEnums::CameraProjection projection;
        float near, far, top, bottom, left, right;
};

#endif