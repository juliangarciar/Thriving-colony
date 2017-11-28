#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include <GraphicEngine/Camera.h>
#include <GraphicEngine/Vector2.h>
#include <GraphicEngine/Vector3.h>
#include <GraphicEngine/Terrain.h>
#include <IOEngine/InputManager.h>
#include <IOEngine/Mouse.h>

class CameraController {
    
    public:
        CameraController();
        ~CameraController();

        void Move(InputManager *receiver, Mouse *cursor, Terrain *terrain);
        void Rotate(InputManager *receiver, Mouse *cursor);

    private:
        Camera *camera;
        // Helpers
        float recipsqrt2;
        // Camera movement variables ============
        bool camMove;
        Vector3<float> camPos, camTar1;
		Vector2<float> delta;
        Vector2<float> direction;
        Vector2<int> cursorPosSaved;
        int screenMarginV, screenMarginH; //Screen margin for movement
        int minZoom, maxZoom; //Zoom for the camera
        float camSpeed, camHeight, Xup, Yup, currentHeight;
        // Camera rotation optimization variables =================
        Vector3<float> camTar2;
        bool rotationMode;
        f32 cosA, sinA;
        f32 rotSpeed, currentAngle, tempAngle, aSinA, bSinA;
        f32 cosASq, aSinASq, bSinASq, bSinATarTemp2X, cosATarTemp2Y, aSinATarTemp2Z;

        //ToDo: Esto no va aqui
        int mapMarginLeft, mapMarginRight, mapMarginTop, mapMarginBottom; //
        Vector2<int> screenCenter; //
};
#endif