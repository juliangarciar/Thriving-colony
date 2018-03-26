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
        void setTargetPosition(glm::vec3 p);

        /**
          * @brief 
          * 
          * @param tX 
          * @param tY 
          * @param tZ 
          */
        void setCameraPosition(glm::vec3 p);

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
        void setNearValue(f32 n);

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
};

#endif