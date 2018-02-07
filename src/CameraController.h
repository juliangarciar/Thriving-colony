#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include <GraphicEngine/Camera.h>
#include <GraphicEngine/Vector2.h>
#include <GraphicEngine/Vector3.h>
#include <GraphicEngine/Terrain.h>
#include <IOEngine/Keyboard.h>
#include <IOEngine/Mouse.h>
#include "Enumeration.h"

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
	* @brief Actualiza CameraController
        * @param deltaTime para la interpolacion
	*/
        void Update(float);

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
        
    private:
        //Camera
        Camera *camera;

        //Camera position
        Vector3<float> camPos, tarPos;
        Vector3<float> userPos;

        //Camera modes
        bool movementMode;
        bool rotationOrInclinationMode;
        bool zoomMode;
	bool centerCameraMode;

        // Camera movement variables
        int screenMarginV, screenMarginH;
        int direction;
        float camSpeed;

        // Camera rotation, inclination
        float rotSpeed;
        float inclSpeed;
        float minInclination, maxInclination;
        Vector2<float> delta;
        Vector3<float> distanceToTarget;

        //Camera zoom variables
        int minZoom, maxZoom;
        int zoomLevels;
        float zoomDistanceFromTarget;
        Vector3<float> cameraPositionIncrement;

        // Helpers and cursor optimizacion variables
        float recipsqrt2;

        int centerMargin;
        Vector2<int> cursorPosSaved;
        
        Vector2<int> screenCenter; //ToDo: Esto no va aqui
};
#endif