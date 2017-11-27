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
    camMove = true;
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

    if (rotationMode){
		if (cursorPosCurrent.x < screenCenter.x){
			delta.x += 10;
		} else if (cursorPosCurrent.x > screenCenter.x) {
			delta.x -= 10;
		}

		if (cursorPosCurrent.y < screenCenter.y){
			delta.y += 10;
		} else if (cursorPosCurrent.y > screenCenter.y) {
			delta.y -= 10;
		}
        
        // reset cursor position to center
        cursor->setPosition(screenCenter.getVectorF());

        // define deltas of cursor data
        delta.x = (delta.x < 0) ? 360+delta.x : delta.x;
        delta.x = (delta.x > 360) ? delta.x-360 : delta.x;
        delta.y = (delta.y < 0) ? 360+delta.y : delta.y;
        delta.y = (delta.y > 360) ? delta.y-360 : delta.y;

		std::cout << "Deltas-- dX: " << delta.x << " dY: " << delta.y << std::endl;

		Vector2<float> position = Vector2<float>(camTar1.x, camTar1.z);
		std::cout << "Pre-- dX: " << position.x << " dY: " << position.y << std::endl;
		Vector2<float> newPosition = position.getFromPolarCoordinates(100, delta.x);
		std::cout << "Pos-- dX: " << newPosition.x << " dY: " << newPosition.y << std::endl;

		camPos.set(newPosition.x, camPos.y, newPosition.y);

		camMove = true;
    }

    if (camMove){
        currentHeight = terrain->getTerrain()->getHeight(camPos.x, camPos.z);

        camPos.y = 0.85f*camPos.y + 0.15f*(currentHeight + camHeight);
		camMove = false;
    }
    
	camera->setCameraPosition(camPos.getVectorF());
	camera->setTargetPosition(camTar1.getVectorF());
}

void CameraController::Rotate(InputManager *receiver, Mouse *cursor){
    // get cursor data
    if (receiver->rightMousePressed())  {
        rotationMode = true;
        cursorPosSaved = cursor->getPosition();
        cursor->setPosition(screenCenter);
    }
    if (receiver->rightMouseReleased()) {
        rotationMode = false;
        cursor->setPosition(cursorPosSaved);
    }
}