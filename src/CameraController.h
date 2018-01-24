#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include <GraphicEngine/Camera.h>
#include <GraphicEngine/Vector2.h>
#include <GraphicEngine/Vector3.h>
#include <GraphicEngine/Terrain.h>
#include <IOEngine/Keyboard.h>
#include <IOEngine/Mouse.h>
#include "Enumeration.h"

class CameraController {
    
    public:
        CameraController(Terrain *t);
        ~CameraController();

        void Update(float deltaTime);

        void Move(Mouse *cursor);
        void RotateAndInclinate(Mouse *cursor);
        void Zoom(Mouse *cursor);

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