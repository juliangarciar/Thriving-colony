#include "CameraController.h"
#include "GraphicEngine/Screen.h"
 
CameraController::CameraController(){
    camera = new Camera();
    camera->setCameraPosition(Vector3<float>(500, 3000, 500));
    //camera->setInclination(Vector2<float>(200, 200));
    camera->setShadowDistance(42000.f);

	recipsqrt2 = camera->getReciprocalSquareroot();
	direction.x = camera->getTargetPosition().x - camera->getCameraPosition().x;
	direction.y = camera->getTargetPosition().z - camera->getCameraPosition().z;
	direction.normalize(); 
	camSpeed = 500.f;
	camHeight = 200.f;
	tarHeight = 160.f;
	minZoom = 150;
	maxZoom = 800;
	marginTop = 50;
	marginLeft = 60;
	mapMarginTop = 100;
	mapMarginLeft = 100;
	mapMarginBottom = 9240;
	mapMarginRight = 9240;
    screenCenter = Vector2<int>(1280/2, 720/2);
	//camPos = position;
	//direction.x = camera->getTargetPosition().x - camera->getCameraPosition().x;
	//direction.y = camera->getTargetPosition().z - camera->getCameraPosition().z;
	//direction.normalize(); 
    camMove = false;
}

CameraController::~CameraController(){

}

//ToDo: Crear camera controller (fuera de fachada) y moverlo ahi
void CameraController::Move(InputManager *receiver, Mouse *cursor, Terrain *terrain) {
	Screen *sc = Screen::Instance();

	if (receiver->getWheelState()) {
		receiver->setWheelState(false);
		if (receiver->isWheelUp()) {
			if (camHeight > minZoom) {
				camHeight -= 20.0f;
				tarHeight -= 20.0f;
				camSpeed -= 0.02f;
			}
		} else {
			if (camHeight < maxZoom) {
				camHeight += 20.0f;
				tarHeight += 20.0f;
				camSpeed += 0.02f;
			}
		}
	}
    
	int n = 0;

    /*n = (receiver->keyDown(KEY_KEY_W) << 0) | (receiver->keyDown(KEY_KEY_A) << 1)
		| receiver->keyDown(KEY_KEY_S) << 2 | receiver->keyDown(KEY_KEY_D) << 3;*/

	Vector2<int> cursorPosCurrent = cursor->getPosition();
	
	if (cursorPosCurrent.y < marginTop){
		n |= 1 << 0;
	} else if (cursorPosCurrent.y > (sc->getScreenHeight() - marginTop)) {
		n |= 1 << 2;
	}

	if (cursorPosCurrent.x < marginLeft){
		n |= 1 << 1;
	} else if (cursorPosCurrent.x > (sc->getScreenWidth() - marginLeft)) {
		n |= 1 << 3;
	}

	// =========================================================================
	camPos.set(camera->getCameraPosition());
	camTar1.set(camera->getTargetPosition());

	if (n != 0) {
		switch (n) {
			// up stands for update (delta)
			case 1:
				Xup = (f32)camSpeed * sc->getDeltaTime() * direction.x;
				Yup = (f32)camSpeed * sc->getDeltaTime() * direction.y;
			break;
			case 2:
				Xup = (f32)-camSpeed * sc->getDeltaTime() * direction.y;
				Yup = (f32)camSpeed * sc->getDeltaTime() * direction.x;
			break;
			case 8:
				Xup = (f32)camSpeed * sc->getDeltaTime() * direction.y;
				Yup = (f32)-camSpeed * sc->getDeltaTime() * direction.x;
			break;
			case 4:
				Xup = (f32)-camSpeed * sc->getDeltaTime() * direction.x;
				Yup = (f32)-camSpeed * sc->getDeltaTime() * direction.y;
			break;
			case 3:
				Xup = (f32)camSpeed * sc->getDeltaTime() * (-direction.y + direction.x) * recipsqrt2;
				Yup = (f32)camSpeed * sc->getDeltaTime() * (direction.x + direction.y) * recipsqrt2;
			break;
			case 9:
				Xup = (f32)camSpeed * sc->getDeltaTime() * (direction.y + direction.x) * recipsqrt2;
				Yup = (f32)camSpeed * sc->getDeltaTime() * (-direction.x + direction.y) * recipsqrt2;
			break;
			case 6:
				Xup = (f32)-camSpeed * sc->getDeltaTime() * (direction.y + direction.x) * recipsqrt2;
				Yup = (f32)camSpeed * sc->getDeltaTime() * (direction.x - direction.y) * recipsqrt2;
			break;
			case 12:
				Xup = camSpeed * sc->getDeltaTime() * (direction.y - direction.x) * recipsqrt2;
				Yup = -camSpeed * sc->getDeltaTime() * (direction.x + direction.y) * recipsqrt2;
			break;
		}

		// border collision + apply update
		if (camPos.x < mapMarginLeft) {
			if (Xup > 0) {
				camPos.x += Xup;
				camTar1.x += Xup;
                camMove = true;
			}
		} else if (camPos.x > mapMarginRight){
			if (Xup < 0) {
				camPos.x += Xup;
				camTar1.x += Xup;
                camMove = true;
			}
		} else {
			camPos.x += Xup;
			camTar1.x += Xup;
            camMove = true;
		}

		if (camPos.z < mapMarginTop) {
			if (Yup > 0) {
				camPos.z += Yup;
				camTar1.z += Yup;
                camMove = true;
			}
		} else if (camPos.z > mapMarginBottom) {
			if (Yup < 0) {
				camPos.z += Yup;
				camTar1.z += Yup;
                camMove = true;
			}
		} else {
			camPos.z += Yup;
			camTar1.z += Yup;
            camMove = true;
		}
	}

    if (camMove){
        currentHeight = terrain->getTerrain()->getHeight(camPos.x, camPos.z);

        camPos.y = 0.85f*camPos.y + 0.15f*(currentHeight + camHeight);
    }

    if (rotationMode){
        //Cursor Position
        deltaX = screenCenter.x - cursorPosCurrent.x;
        deltaY = screenCenter.y - cursorPosCurrent.y;
        
        // reset cursor position to center
        cursor->setPosition(screenCenter.getVectorF());

        // define deltas of cursor data
        deltaX = (deltaX < 130) ? deltaX : 130;
        deltaX = (deltaX > -130) ? deltaX : -130;
        deltaY = (deltaY < 130) ? deltaY : 130;
        deltaY = (deltaY > -130) ? deltaY : -130;

        // complex number rotation along azimuthal angle theta ===================
        tempAngle = deltaX*rotSpeed;
        cosA = cos(tempAngle);
        sinA = sin(tempAngle);

        camTar2 = camTar1 - camPos;

        camTar1.x = cosA*camTar2.x - sinA*camTar2.z;
        camTar1.y = camTar2.y;
        camTar1.z = cosA*camTar2.z + sinA*camTar2.x;

        direction.x = camTar1.x;
        direction.y = camTar1.z;
        direction.normalize();

        // quaternion rotation along polar angle phi =============================

        tempAngle = deltaY*rotSpeed / 2;
        currentAngle = acos(camTar1.y / camTar1.getLength());

        if (currentAngle > 2.84f)
            tempAngle = tempAngle > 0 ? tempAngle : 0;
        else if (currentAngle < 0.3f)
            tempAngle = tempAngle < 0 ? tempAngle : 0;

        cosA = cos(tempAngle);
        sinA = sin(tempAngle);

        aSinA = -sinA*direction.y;
        bSinA = sinA*direction.x;

        cosASq = cosA*cosA;
        aSinASq = aSinA*aSinA;
        bSinASq = bSinA*bSinA;

        bSinATarTemp2X = bSinA*camTar1.x;
        cosATarTemp2Y = cosA*camTar1.y;
        aSinATarTemp2Z = aSinA*camTar1.z;

        camTar2.x = camTar1.x*(cosASq + aSinASq - bSinASq) + 2.0f * bSinA*(aSinATarTemp2Z - cosATarTemp2Y);
        camTar2.y = camTar1.y*(cosASq - aSinASq - bSinASq) + 2.0f * cosA*(bSinATarTemp2X - aSinATarTemp2Z);
        camTar2.z = camTar1.z*(cosASq - aSinASq + bSinASq) + 2.0f * aSinA*(bSinATarTemp2X + cosATarTemp2Y);

        tarHeight = camTar2.y + camHeight;

        std::cout << camTar1.x << " " << camTar1.y << " " << camTar1.z << "\n";
        camTar1 = camTar2 + camPos;
        std::cout << camTar1.x << " " << camTar1.y << " " << camTar1.z << "\n";
    }
    
	camera->setCameraPosition(camPos.getVectorF());
	camera->setTargetPosition(camTar1.getVectorF());
}

void CameraController::Rotate(InputManager *receiver, Mouse *cursor){
    // get cursor data
    if (receiver->middleMousePressed())  {
        rotationMode = true;
        cursorPosSaved = cursor->getPosition();
        cursor->setPosition(screenCenter);
        deltaX = 0;
        deltaY = 0;
    }
    if (receiver->middleMouseReleased()) {
        rotationMode = false;
        cursor->setPosition(cursorPosSaved);
    }
}