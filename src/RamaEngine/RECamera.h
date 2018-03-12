#ifndef RECAMERA_H
#define RECAMERA_H

#include "RETypes.h"
#include "REEnums.h"
#include "Graphics/TNode.h"
#include "Graphics/TTransform.h"
#include "Graphics/TCamera.h"

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
        void setFarValue(f32 f);

        /**
         * @brief 
         * 
         */
        void setPerspectiveProjection();

        /**
         * @brief 
         * 
         */
        void setParallelProjection();

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
        void setTargetPosition(glm::vec3 p);

        /**
          * @brief 
          * 
          * @param tX 
          * @param tY 
          * @param tZ 
          */
        void setCameraPosition(glm::vec3 p);

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
        f32 getFov();

        /**
         * @brief 
         * 
         * @return TEnums::CameraProjection 
         */
        REEnums::CameraProjection getProjectionMode();

        /**
         * @brief 
         * 
         * @return glm::vec3 
         */
        glm::vec3 getCameraPosition();

        /**
         * @brief 
         * 
         * @return glm::vec3 
         */
        glm::vec3 getTargetPosition();
        
        /**
         * @brief 
         * 
         * @return TNode* 
         */
        TNode* getCameraNode();

        /**
         * @brief 
         * 
         * @return TCamera* 
         */
        TCamera* getCameraEntity();
    private:
        TNode* cameraNode;
        TNode* rotationNode;
        TNode* translationNode;
        TNode* scaleNode;
};

#endif