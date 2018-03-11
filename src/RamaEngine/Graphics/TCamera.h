#ifndef TCAMERA_H
#define TCAMERA_H

#include "TEntity.h"

class TCamera : public TEntity {
    public:
        /**
         * @brief constructs a new camera entity to be used on a node.
         * 
         * @param REEnums::CameraProjection projection mode.
         * @param f32 near.
         * @param f32 far.
         * @param f32 top.
         * @param f32 bottom.
         * @param f32 left.
         * @param f32 right.
         * @param bool
         */
        TCamera(REEnums::CameraProjection, f32, f32, f32, f32, f32, f32, bool = true);

        /**
         * @brief Destructor for a camera entity.
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
         * @brief fills the projection matrix with a perspective one based on the parameters.
         * 
         * 
         */
        void setPerspective();

        /**
         * @brief 
         * 
         */
        void setParallel();

        /**
         * @brief sets the current projection mode to the one specified as parameter.
         * 
         * @param REEnums::CameraProjection new projection mode.
         */
        void setProjection(REEnums::CameraProjection);

        /**
         * @brief set the camera to active or inactive
         * 
         * @param bool new camera active state
         */
        void setActive(bool);

        /**
         * @brief sets the distance from the camera at which sits the near plane.
         * 
         * @param f32 distance.
         */
        void setNear(f32);

        /**
         * @brief sets the distance from the camera at which sits the far plane.
         * 
         * @param f32 distance.
         */
        void setFar(f32);

        /**
         * @brief set the field of view to the angular amount specified as a parameter.
         * 
         * @param f32 field of view. This is expressed in radians if GLM_FORCE_RADIANS is define or degrees otherwise.
         */
        void setFov(f32);
        
        /**
         * @brief set the top border to the amount specified as a parameter.
         * 
         * @param f32 top border.
         */
        void setTop(f32);

        /**
         * @brief set the bottom border to the amount specified as a parameter.
         * 
         * @param f32 bottom border.
         */
        void setBottom(f32);

        /**
         * @brief set the left border to the amount specified as a parameter.
         * 
         * @param f32 left border.
         */
        void setLeft(f32);

        /**
         * @brief set the right border to the amount specified as a parameter.
         * 
         * @param f32 right border.
         */
        void setRight(f32);

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
         * @brief Return the current projection mode.
         * 
         * @return REEnums::CameraProjection current projection mode.
         */
        REEnums::CameraProjection getProjection();

        /**
         * @brief returns wether or not the camera is active
         * 
         * @return true if the camera is active
         * @return false otherwise
         */
        bool getActive();

        /**
         * @brief return the distance at which sits the near plane of the camera.
         * 
         * @return f32 distance between the camera and the near plane.
         */
        f32 getNear();

        /**
         * @brief return the distance at which sits the far plane of the camera.
         * 
         * @return f32 distance between the camera and the far plane.
         */
        f32 getFar();

        /**
         * @brief returns the field of vision of the camera.
         * 
         * @return f32 field of vision.
         */
        f32 getFov();

        /**
         * @brief returns the top border of the camera.
         * 
         * @return f32 top border.
         */
        f32 getTop();

        /**
         * @brief returns the bottom border of the camera.
         * 
         * @return f32 bottom border.
         */
        f32 getBottom();

        /**
         * @brief returns the left border of the camera.
         * 
         * @return f32 left border.
         */
        f32 getLeft();

        /**
         * @brief returns the right border.
         * 
         * @return f32 right border.
         */
        f32 getRight();

        /**
         * @brief 
         * 
         * @return glm::vec3 
         */
        glm::vec3 getTargetPosition();

        /**
         * @brief 
         * 
         * @return glm::vec3 
         */
        glm::vec3 getCameraPosition();

        /**
         * @brief 
         * 
         */
        void calculateViewMatrix();

        /**
         * @brief 
         * 
         */
        void assignViewMatrix();

    private:
        glm::vec3 targetPosition;
        glm::vec3 cameraPosition;
        // View matrix
        glm::mat4 vMat;

        REEnums::CameraProjection projection;
        // Field of view (fov) is expressed in radians if GLM_FORCE_RADIANS is define or degrees otherwise.
        f32 near, far, fov, top, bottom, left, right;

        bool active;
};

#endif