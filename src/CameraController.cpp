#include "CameraController.h"
#include "Game.h"
  
CameraController::CameraController(Terrain *t) {
	terrain = t;

	//Camera 
    camera = new Camera();
    camera -> setShadowDistance(42000.f);

	// Helper initializations
	recipsqrt2 = camera -> getReciprocalSquareroot();

	// Cam movement initializations
	direction = 0;
	camSpeed = 700.0f; // Esto estaba a 500
	screenMarginV = 20;
	screenMarginH = 20;
    movementMode = false;

	// Cam zoom initializations
	camHeight = 750.0f;
	minZoom = 500;
	maxZoom = 1000;
    zoomMode = false;

	// Cam rotation and inclination initializations
	rotSpeed = 2.f;
	inclSpeed = 20.f;
	delta.y = 200.f;
	minInclination = 100.f;
	maxInclination = 1000.f;
	centerMargin = 20;
    rotationOrInclinationMode = false;

	//ToDo: esto no va aqui
	mapMarginTop = 1500;
	mapMarginLeft = 1500;
	mapMarginBottom = 8000;
	mapMarginRight = 8000;
    screenCenter = Vector2<int>(1280/2, 720/2);

	int posX = HUMAN_CITY_HALL_X;
	int posZ = HUMAN_CITY_HALL_Z;
	int posY = terrain -> getY(posX, posZ) + camHeight;

	//Posiciones iniciales de la camara
	Vector2<float> camPos2D = Vector2<float>(posX, posZ).getFromPolarCoordinates(delta.y, 0);
	camera -> setCameraPosition(Vector3<float>(camPos2D.x, posY, camPos2D.y));
    camera -> setTargetPosition(Vector3<float>(posX, terrain -> getY(posX, posZ), posZ));
}

CameraController::~CameraController() {
	delete camera;
}

void CameraController::Update(float deltaTime) {
	camPos.set(camera -> getCameraPosition());
	tarPos.set(camera -> getTargetPosition());

    if (rotationOrInclinationMode) {
		Vector2<float> camPos2D = Vector2<float>(tarPos.x, tarPos.z).getFromPolarCoordinates(delta.y, delta.x);
		camPos.set(camPos2D.x, camPos.y, camPos2D.y);
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
		} else if (camPos.x > mapMarginRight) {
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

    if (movementMode || zoomMode || rotationOrInclinationMode){
        currentHeight = terrain -> getY(camPos.x, camPos.z);
        camPos.y = currentHeight + camHeight;

		camera -> setCameraPosition(camPos.getVectorF());
		camera -> setTargetPosition(tarPos.getVectorF());
    }
	
	if (Game::Instance() -> getKeyboard() -> keyPressed(GLFW_KEY_SPACE)) {
		if(Human::getInstance() -> getUnitManager() -> getSelectedTroop() != NULL) {
			camPos.x = Human::getInstance() -> getUnitManager() -> getSelectedTroop() -> getPosition() -> x;
			camPos.z = Human::getInstance() -> getUnitManager() -> getSelectedTroop() -> getPosition() -> z;
			camPos.y = terrain -> getY(camPos.x, camPos.z) + camHeight;
		} else {
			camPos.x = HUMAN_CITY_HALL_X;
			camPos.z = HUMAN_CITY_HALL_Z;
			camPos.y = terrain -> getY(camPos.x, camPos.z) + camHeight;
			
		}
		Vector2<float> camPos2D = Vector2<float>(camPos.x, camPos.z).getFromPolarCoordinates(delta.y, 0);
		camera -> setCameraPosition(Vector3<float>(camPos2D.x, camPos.y, camPos2D.y));
		camera -> setTargetPosition(Vector3<float>(camPos.x, terrain -> getY(camPos.x, camPos.z), camPos.z));
	}
}

void CameraController::Move(Mouse *cursor) {
	Window *sc = Window::Instance();

    /*direction = (receiver -> keyDown(KEY_KEY_W) << 0) | (receiver -> keyDown(KEY_KEY_A) << 1)
		| receiver -> keyDown(KEY_KEY_S) << 2 | receiver -> keyDown(KEY_KEY_D) << 3;*/

	direction = 0;
	movementMode = false;

	Vector2<int> cursorPosCurrent = cursor -> getPosition();

	if (cursorPosCurrent.x <= 0) cursorPosCurrent.x = 0;
	else if (cursorPosCurrent.x >= sc -> getRealWindowWidth()) cursorPosCurrent.x = sc -> getRealWindowWidth();

	if (cursorPosCurrent.y <= 0) cursorPosCurrent.y = 0;
	else if (cursorPosCurrent.y >= sc -> getRealWindowHeight()) cursorPosCurrent.y = sc -> getRealWindowHeight();

	cursor -> setPosition(cursorPosCurrent);
	
	if (cursorPosCurrent.y < screenMarginV) {
		direction |= 1 << 0;
        movementMode = true;
	} else if (cursorPosCurrent.y > (sc -> getRealWindowHeight() - screenMarginV)) {
		direction |= 1 << 2;
        movementMode = true;
	}

	if (cursorPosCurrent.x < screenMarginH) {
		direction |= 1 << 1;
        movementMode = true;
	} else if (cursorPosCurrent.x > (sc -> getRealWindowWidth() - screenMarginH)) {
		direction |= 1 << 3;
        movementMode = true;
	}
}

void CameraController::Zoom(Mouse *cursor){
	zoomMode = false;
	if (cursor -> getWheelY() > 0.0f) {
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

void CameraController::RotateAndInclinate(Mouse *cursor){
    // get cursor data
    if (cursor -> middleMousePressed()) {
        rotationOrInclinationMode = true;
        cursorPosSaved = cursor -> getPosition();
        cursor -> setPosition(screenCenter);

		Game::Instance() -> getCursor() -> hide();
    }
    if (cursor -> middleMouseReleased()) {
        rotationOrInclinationMode = false;
        cursor -> setPosition(cursorPosSaved);
		
		Game::Instance() -> getCursor() -> show();
    }
	if (rotationOrInclinationMode) {
		Vector2<int> cursorPosCurrent = cursor -> getPosition();

		//Increase or decease rotation angle
		if (cursorPosCurrent.x < screenCenter.x - centerMargin) {
			delta.x += rotSpeed;
		} else if (cursorPosCurrent.x > screenCenter.x + centerMargin) {
			delta.x -= rotSpeed;
		}

		//Increase or decease inclination angle
		if (cursorPosCurrent.y < screenCenter.y - centerMargin) {
			delta.y += inclSpeed;
		} else if (cursorPosCurrent.y > screenCenter.y + centerMargin) {
			delta.y -= inclSpeed;
		}

        // fix if they are offlimits
        delta.x = (delta.x < 0) ? 360+delta.x : delta.x;
        delta.x = (delta.x > 360) ? delta.x-360 : delta.x;

        // fix if they are offlimits
        delta.y = (delta.y < minInclination) ? minInclination : delta.y;
        delta.y = (delta.y > maxInclination) ? maxInclination : delta.y;

        // reset cursor position to center
        cursor -> setPosition(screenCenter.getVectorF());
	}
}

Camera *CameraController::getCamera() {
	return camera;
}