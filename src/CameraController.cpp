#include "CameraController.h"
#include "GraphicEngine/Screen.h"
  
CameraController::CameraController(){
	//Camera 
    camera = new Camera();
    camera->setShadowDistance(42000.f);

	// Helper initializations
	recipsqrt2 = camera->getReciprocalSquareroot();

	// Cam movement initializations
	direction = 0;
	camSpeed = 500.f;
	screenMarginV = 50;
	screenMarginH = 60;
    movementMode = false;

	// Cam zoom initializations
	camHeight = 3500.f;
	minZoom = 3150;
	maxZoom = 3800;
    zoomMode = false;

	// Cam rotation initializations
	rotSpeed = 2;
    rotationMode = false;

	// Cam inclination initializations
	inclination = 500.f;
	minInclination = 100.f;
	maxInclination = 1000.f;
	inclinationMode = false;

	//Posiciones iniciales de la camara
	Vector2<float> camPos2D = Vector2<float>().getFromPolarCoordinates(inclination, 0);
	camera->setCameraPosition(Vector3<float>(camPos2D.x, camHeight, camPos2D.y));
    camera->setTargetPosition(Vector3<float>(0, 0, 0));
	std::cout << "camPos2D X " << camPos2D.x << " Z " << camPos2D.y << std::endl;

	//ToDo: esto no va aqui
	mapMarginTop = 100;
	mapMarginLeft = 100;
	mapMarginBottom = 9240;
	mapMarginRight = 9240;
    screenCenter = Vector2<int>(1280/2, 720/2);
}

CameraController::~CameraController(){

}

void CameraController::Update(Terrain *terrain, float deltaTime){
	camPos.set(camera->getCameraPosition());
	tarPos.set(camera->getTargetPosition());

    if (rotationMode){
		Vector2<float> camPos2D = Vector2<float>(tarPos.x, tarPos.z).getFromPolarCoordinates(inclination, delta.x);
		camPos.set(camPos2D.x, camPos.y, camPos2D.y);
    }

	if (inclinationMode){
	}

	if (movementMode) {
		int d = delta.x; 
		switch (direction) {
			// up stands for update (delta)
			case 1: //arriba
				camIncr.x = (float)camSpeed * deltaTime;
				camIncr.y = (float)camSpeed * deltaTime;
				d += 180;
			break;
			case 8: //derecha
				camIncr.x = (float)camSpeed * deltaTime;
				camIncr.y = (float)-camSpeed * deltaTime;
				d += 90;
			break;
			case 4: //abajo
				camIncr.x = (float)-camSpeed * deltaTime;
				camIncr.y = (float)-camSpeed * deltaTime;
				d += 0;
			break;
			case 2: // izquierda
				camIncr.x = (float)-camSpeed * deltaTime;
				camIncr.y = (float)camSpeed * deltaTime;
				d += 270;
			break;
			case 9: // arriba derecha
				camIncr.x = (float)camSpeed * deltaTime * recipsqrt2;
				camIncr.y = (float)camSpeed * deltaTime * recipsqrt2;
				d+= 135;
			break;
			case 12: //abajo derecha
				camIncr.x = (float)camSpeed * deltaTime * recipsqrt2;
				camIncr.y = (float)-camSpeed * deltaTime * recipsqrt2;
				d += 45;
			break;
			case 6: //abajo izquierda
				camIncr.x = (float)-camSpeed * deltaTime * recipsqrt2;
				camIncr.y = (float)camSpeed * deltaTime * recipsqrt2;
				d += 315;
			break;
			case 3: // arriba izquierda
				camIncr.x = (float)camSpeed * deltaTime * recipsqrt2;
				camIncr.y = (float)camSpeed * deltaTime * recipsqrt2;
				d += 225;
			break;
		}

		camIncr = vector0.getFromPolarCoordinates(
			sqrtf(powf(camIncr.x, 2) + powf(camIncr.y, 2)), 
			d
		);

		// border collision + apply update
		if (camPos.x < mapMarginLeft) {
			if (camIncr.x > 0) {
				camPos.x += camIncr.x;
				tarPos.x += camIncr.x;
			}
		} else if (camPos.x > mapMarginRight){
			if (camIncr.x < 0) {
				camPos.x += camIncr.x;
				tarPos.x += camIncr.x;
			}
		} else {
			camPos.x += camIncr.x;
			tarPos.x += camIncr.x;
		}

		if (camPos.z < mapMarginTop) {
			if (camIncr.y > 0) {
				camPos.z += camIncr.y;
				tarPos.z += camIncr.y;
			}
		} else if (camPos.z > mapMarginBottom) {
			if (camIncr.y < 0) {
				camPos.z += camIncr.y;
				tarPos.z += camIncr.y;
			}
		} else {
			camPos.z += camIncr.y;
			tarPos.z += camIncr.y;
		}
	}

    if (movementMode || zoomMode || rotationMode || inclinationMode){
        currentHeight = terrain->getTerrain()->getHeight(camPos.x, camPos.z);
        camPos.y = currentHeight + camHeight;

		camera->setCameraPosition(camPos.getVectorF());
		camera->setTargetPosition(tarPos.getVectorF());
    }
}

//ToDo: Crear camera controller (fuera de fachada) y moverlo ahi
void CameraController::Move(InputManager *receiver, Mouse *cursor) {
	Screen *sc = Screen::Instance();

    /*direction = (receiver->keyDown(KEY_KEY_W) << 0) | (receiver->keyDown(KEY_KEY_A) << 1)
		| receiver->keyDown(KEY_KEY_S) << 2 | receiver->keyDown(KEY_KEY_D) << 3;*/

	direction = 0;
	movementMode = false;

	Vector2<int> cursorPosCurrent = cursor->getPosition();
	
	if (cursorPosCurrent.y < screenMarginV){
		direction |= 1 << 0;
        movementMode = true;
	} else if (cursorPosCurrent.y > (sc->getScreenHeight() - screenMarginV)) {
		direction |= 1 << 2;
        movementMode = true;
	}

	if (cursorPosCurrent.x < screenMarginH){
		direction |= 1 << 1;
        movementMode = true;
	} else if (cursorPosCurrent.x > (sc->getScreenWidth() - screenMarginH)) {
		direction |= 1 << 3;
        movementMode = true;
	}
}

void CameraController::Zoom(InputManager *receiver){
	zoomMode = false;
	if (receiver->getWheelState()) {
		receiver->setWheelState(false);
		if (receiver->isWheelUp()) {
			if (camHeight > minZoom) {
				camHeight -= 20.0f;
				camSpeed -= 0.02f;
		        zoomMode = true;
			}
		} else {
			if (camHeight < maxZoom) {
				camHeight += 20.0f;
				camSpeed += 0.02f;
		        zoomMode = true;
			}
		}
	}
}

void CameraController::Rotate(InputManager *receiver, Mouse *cursor){
    // get cursor data
    if (receiver->rightMousePressed()) {
        rotationMode = true;
        cursorPosSaved = cursor->getPosition();
        cursor->setPosition(screenCenter);
    }
    if (receiver->rightMouseReleased()) {
        rotationMode = false;
        cursor->setPosition(cursorPosSaved);
    }
	if (rotationMode){
		Vector2<int> cursorPosCurrent = cursor->getPosition();
		//Increase or decease rotation angle
		if (cursorPosCurrent.x < screenCenter.x){
			delta.x += rotSpeed;
		} else if (cursorPosCurrent.x > screenCenter.x) {
			delta.x -= rotSpeed;
		}

        // fix if they are offlimits
        delta.x = (delta.x < 0) ? 360+delta.x : delta.x;
        delta.x = (delta.x > 360) ? delta.x-360 : delta.x;
        
        // reset cursor position to center
        cursor->setPosition(screenCenter.getVectorF());
	}
}

void CameraController::Inclinate(InputManager *receiver, Mouse *cursor){
    // get cursor data
    if (receiver->rightMousePressed()) {
        inclinationMode = true;
        cursorPosSaved = cursor->getPosition();
        cursor->setPosition(screenCenter);
    }
    if (receiver->rightMouseReleased()) {
        inclinationMode = false;
        cursor->setPosition(cursorPosSaved);
    }
	if (inclinationMode){
		Vector2<int> cursorPosCurrent = cursor->getPosition();
		//Increase or decease rotation angle
		if (cursorPosCurrent.x < screenCenter.x){
			//delta.y += inclSpeed;
		} else if (cursorPosCurrent.x > screenCenter.x) {
			//delta.y -= inclSpeed;
		}

        // fix if they are offlimits
        delta.y = (delta.y < 0) ? 360+delta.y : delta.y; //ToDo: el limite de la inclinacion es otro
        delta.y = (delta.y > 360) ? delta.y-360 : delta.y; //ToDo: el limite de la inclinacion es otro
        
        // reset cursor position to center
        cursor->setPosition(screenCenter.getVectorF());
	}
}

Camera *CameraController::getCamera(){
	return camera;
}