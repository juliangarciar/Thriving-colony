#ifndef OBDCAMERA_H
#define OBDCAMERA_H

#include "OBDEntity.h"
#include "OBDSceneNode.h"

#include "Graphics/TTransform.h"
#include "Graphics/TCamera.h"

class OBDCamera {
    public:
        /**
         * @brief Construct a new OBDCamera object
         * 
         * @param parent node
         * @param screen width
         * @param screen height
         * @param far distance
         * @param field of view
         * 
         */
        OBDCamera(OBDSceneNode* parent, i32, i32, f32, f32);

        /**
         * @brief Destroy the OBDCamera object
         * 
         */
        virtual ~OBDCamera();

        /**
         * @brief Set the Target Position 
         * 
         * @param p new target position
         */
        void setTargetPosition(glm::vec3 p);

        /**
         * @brief Set the Camera Position
         * 
         * @param p new camera position
         */
        void setCameraPosition(glm::vec3 p);

        /**
         * @brief set sitch on or off the the camera
         * 
         * @param active new active status
         */
        void setActive(bool active);

        /**
         * @brief set a new distance to the near plane.
         * 
         * @param n new near value
         */
        void setNearValue(f32 n);

        /**
         * @brief set a new distance to the far plane
         * 
         * @param f new far value
         */
        void setFarValue(f32 f);

        /**
         * @brief change to perspective projection.
         * 
         */
        void setPerspectiveProjection();

        /**
         * @brief change to parallel projection
         * 
         */
        void setParallelProjection();

        /**
         * @brief set a new field of view
         * 
         * @param fov field of view
         */
        void setFov(f32 fov);

        /**
         * @brief returns weteher or not the camera is active
         * 
         */
        bool getActive();

        /**
         * @brief returns at which distance sits the near plane
         * 
         * @return f32 near distance
         */
        f32 getNear();

        /**
         * @brief return at which distance sits the far plane
         * 
         * @return f32 far distance
         */
        f32 getFar();

        /**
         * @brief returns the field of view
         * 
         * @return f32 field of view
         */
        f32 getFov();

        /**
         * @brief returns the current projection mode of the camera.
         * 
         * @return TEnums::CameraProjection current projection mode.
         */
        OBDEnums::CameraProjection getProjectionMode();

        /**
         * @brief returns the camera position.
         * 
         * @return glm::vec3 position of the camera.
         */
        glm::vec3 getCameraPosition();

        /**
         * @brief return the target position
         * 
         * @return glm::vec3 position of the target.
         */
        glm::vec3 getTargetPosition();
		
        /**
         * @brief get this' camera entity.
         * 
         * @return TCamera* camera entity.
         */
        TCamera* getCameraEntity();

        /**
         * @brief Get the First Node object
         * 
         * @return TNode* 
         */
        TNode *getFirstNode();
    private:
        TNode* cameraNode;
};

#endif