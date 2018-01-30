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
         * @param terrain para calcular la altura del terreno
		 */
        CameraController(Terrain *);
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
         * @param cursor de tipo mouse, para moverla segun la posicion de este
		 */
        void Move(Mouse *);
        /**
		 * @brief Rota e inclina la camara
         * @param cursor de tipo mouse, para rotarla e inclinarla segun la posicion de este
		 */
        void RotateAndInclinate(Mouse *);
        /**
		 * @brief Hace zoom a la camara
         * @param cursor de tipo mouse, para hacerle zoom a la camara segun la posicion de este
		 */
        void Zoom(Mouse *);

        /**
		 * @brief devuelve la camara activa
         * @return camara de tipo Camera
		 */
        Camera *getCamera();
        
    private:
        //Helpers
        Terrain *terrain;
        //Camera
        Camera *camera;
        //Camera modes
        bool movementMode;
        bool rotationOrInclinationMode;
        bool zoomMode;

        // Helpers
        float recipsqrt2;
		Vector2<float> vector0;
        Vector3<float> camPos, tarPos;

        // Camera movement variables
        int screenMarginV, screenMarginH;
        int direction;
        float camSpeed;
        Vector2<float> camIncr;

        // Camera rotation, inclination and cursor optimizacion variables
        float rotSpeed;
        float inclSpeed;
		Vector2<float> delta;
        float minInclination, maxInclination;

        int centerMargin;
        Vector2<int> cursorPosSaved;

        //Camera zoom variables
        int minZoom, maxZoom;
        float camHeight, currentHeight;

        //ToDo: Esto no va aqui
        int mapMarginLeft, mapMarginRight, mapMarginTop, mapMarginBottom; //
        Vector2<int> screenCenter; //
};
#endif