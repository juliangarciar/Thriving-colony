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
 * @class CameraController
 * @brief Crea un objeto tipo CameraController
 */
class CameraController {
    
    public:
        /**
	* @brief Constructor
	*/
        CameraController();
        /**
	* @brief Destructor
	*/
        ~CameraController();

        /**
         * @brief Inicia el sistema de camara
         * 
         */
        void Init(Vector3<float>);

        /**
	* @brief Actualiza CameraController
        * @param deltaTime para la interpolacion
	*/
        void Update(f32);

        /**
	 * @brief Mueve la camara
	 */
        void Move();
        /**
	 * @brief Rota e inclina la camara
	 */
        void RotateAndInclinate();
        /**
	 * @brief Hace zoom a la camara
	 */
        void Zoom();
        /**
         * @brief Centra la camara
         */
        void CenterCamera();

        /**
	 * @brief devuelve la camara activa
         * @return camara de tipo Camera
	 */
        Camera *getCamera();
        
        /**
         * @brief 
         * 
         * @param i32 
         */
        void setZoomDistanceFromTarget(i32);
        
        /**
         * @brief 
         * 
         * @param i32 
         * @param i32 
         */
        void setRotateDegrees(i32, i32);

        Vector3<f32> getTarPos();
        Vector3<f32> getCameraPosition();  
        
    private:
        //Camera
        Camera *camera;

        //Camera position
        Vector3<f32> camPos, tarPos;
        Vector3<f32> userPos;

        //Camera modes
        bool movementMode;
        bool rotationOrInclinationMode;
        bool zoomMode;
	bool centerCameraMode;

        // Camera movement variables
        i32 screenMarginV, screenMarginH;
        i32 direction;
        f32 camSpeed;

        // Camera rotation, inclination
        f32 rotSpeed;
        f32 inclSpeed;
        f32 minInclination, maxInclination;
        Vector2<f32> rotateDegrees;
        Vector3<f32> distanceToTarget;

        //Camera zoom variables
        i32 minZoom, maxZoom;
        i32 zoomLevels;
        f32 zoomDistanceFromTarget;
        Vector3<f32> cameraPositionIncrement;

        // Helpers and cursor optimizacion variables
        f32 recipsqrt2;

        i32 centerMargin;
        Vector2<i32> cursorPosSaved;
        
        Vector2<i32> screenCenter; //ToDo: Esto no va aqui
};
#endif