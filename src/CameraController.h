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
#include <IOEngine/Timer.h>

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
		* 
		* @param Vector3 that will be the target position.
		*/
		void Init(Vector3<float>);

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
		* 
		* @return A pointer to an object of Camera type.
		*/
		Camera *getCamera();

		/**
		* @brief Get the position of the current target.
		* 
		* @return Vector3 with the value of tarPos variable.
		*/
		Vector3<f32> getTargetPosition();

		/**
		* @brief Get the current position of the camera.
		* 
		* @return Vector3 with the value of camPos variable.
		*/
		Vector3<f32> getCameraPosition();

		//Edges of the window. 
		Vector2<f32> screenMargin;

		//Center of the screen margin for rotation/inclination
		Vector2<f32> centerMargin;

		//Speed at which the camera is going to move.
		f32 camSpeed;

		//Speed at which the camera is going to rotate.
		f32 rotSpeed;

		//Speed at which the camera is going to tilt.
		f32 inclSpeed;

		//Number of times you can scroll for zoom
		i32 zoomLevels;

		//Minimum tilt of the camera.
		f32 minInclination;

		//Maximum tilt of the camera.
		i32 maxInclination;

		//Minimun zoom of the camera.
		i32 minZoom;
		
		//Maximum zoom of the camera.
		i32 maxZoom;

		//Initial rotation degrees of the camera.
		Vector2<f32> rotateDegrees;

		//Initial distance from the target position to the camera position.
		Vector3<f32> distanceToTarget;

		//Initial zoom distance from target
		f32 zoomDistanceFromTarget;
	private:
		/**
		* @brief 
		* 
		* @param deltaTime 
		*/
		void updateCamera(f32 deltaTime);

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

		//Camera direction
		i32 direction;

		//
		f32 recipsqrt2;

		//Current mouse cursor position.
		Vector2<i32> cursorPosSaved;
		
		//LoD timer
		Timer* updateTimer;
};
#endif