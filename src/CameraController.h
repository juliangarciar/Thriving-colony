#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include <Types.h>
#include <Enumeration.h>
#include <MathEngine/Vector2.h>
#include <MathEngine/Vector3.h>
#include <GraphicEngine/Camera.h>
#include <GraphicEngine/Terrain.h>
#include <IOEngine/Keyboard.h>
#include <IOEngine/Mouse.h>

/**
 * @class CameraController.
 * @brief Create a CameraController type object.
 */
class CameraController {
    
    public:
        /**
	* @brief CameraController constructor
	*/
        CameraController();

        /**
	* @brief CameraController destructor
	*/
        ~CameraController();

        /**
         * @brief Set camera and target positions and the distance to the target.
         * @param Vector3 that will be the target position.
         */
        void Init(Vector2<float>);

        /**
	* @brief Update target and camera position based on the changes done since the last update.
        * @param f32 that will be the delta time to do the interpolation.
	*/
        void Update(f32);

        /**
	 * @brief Move the camera up, down, right or left if the mouse cursor is on the up, down, right or left edge of the window.
	 */
        void Move();

        /**
	 * @brief Rotate the camera if the middle bottom of the mouse is pressed.
	 */
        void RotateAndInclinate();

        /**
	 * @brief Zoom in or out when the wheel of the mouse is used.
	 */
        void Zoom();

        /**
         * @brief Change the target of the camera to the current selected troop or to the human player's command center if there is none selected troop when the space key is pressed.
         */
        void CenterCamera();

        /**
	 * @brief Get the current active camera.
         * @return A pointer to an object of Camera type.
	 */
        Camera *getCamera();
        
        /**
         * @brief Set the value of zoomDistanceFromTarget variable.
         * @param i32 is the value that will be assigned to zoomDistanceFromTarget variable.
         */
        void setZoomDistanceFromTarget(i32);
        
        /**
         * @brief Set the value of rotateDegrees variable.
         * @param i32 x is the value that will be assigned to the x component of rotateDegrees variable.
         * @param i32 y is the value that will be assigned to the y component of rotateDegrees variable. 
         */
        void setRotateDegrees(i32 x, i32 y);

        /**
         * @brief Get the position of the current target.
         * @return Vector3 with the value of tarPos variable.
         */
        Vector3<f32> getTarPos();

        /**
         * @brief Get the current position of the camera.
         * @return Vector3 with the value of camPos variable.
         */
        Vector3<f32> getCameraPosition();  
        
    private:
        //Pointer to the current active camera.
        Camera *camera;

        //Camera position
        Vector3<f32> camPos;

        //Target position
        Vector3<f32> tarPos;

        //User pòsition
        Vector3<f32> userPos;

        //True when the camera has moved since the last update and false in other case.
        bool movementMode;

        //True when the camera has been rotated since the last update and false in other case.
        bool rotationOrInclinationMode;

        //True when the camera has been zoomed in or out since the last update and false in other case.
        bool zoomMode;

        //True when the space has been pressed since the last update and false in other case.
	bool centerCameraMode;

        //Up and down edges of the window. 
        i32 screenMarginV;

        //Right and left edges of the window.
        i32 screenMarginH;

        //
        i32 direction;

        //Speed at which the camera is going to move.
        f32 camSpeed;

        //Speed at which the camera is going to rotate.
        f32 rotSpeed;

        //Speed at which the camera is going to tilt.
        f32 inclSpeed;

        //Minimum tilt of the camera.
        f32 minInclination;

        //Maximum tilt of the camera.
        i32 maxInclination;

        //Current rotate degrees of the camera.
        Vector2<f32> rotateDegrees;

        //Current distance from the target position to the camera position.
        Vector3<f32> distanceToTarget;

        //Minimun zoom of the camera.
        i32 minZoom;
        
        //Maximum zoom of the camera.
        i32 maxZoom;

        //
        i32 zoomLevels;

        //
        f32 zoomDistanceFromTarget;

        //
        f32 recipsqrt2;

        //
        i32 centerMargin;

        //Current mouse cursor position.
        Vector2<i32> cursorPosSaved;
        
        //Center point of the current window size.
        Vector2<i32> screenCenter; //ToDo: Esto no va aqui
};
#endif