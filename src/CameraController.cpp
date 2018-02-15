#include "CameraController.h"
#include "Game.h"
  
CameraController::CameraController() {
	Game *g = Game::Instance();
	Window *w = g->getWindow();

	//Camera 
    camera = new Camera();
    camera -> setShadowDistance(42000.f);

	// Initial position of the target
	i32 targetX = Enumeration::HumanCityHall::human_x;
	i32 targetZ = Enumeration::HumanCityHall::human_z;
	i32 targetY = Map::Instance() -> getTerrain() -> getY(targetX, targetZ);

	// Helper initializations
	recipsqrt2 = camera -> getReciprocalSquareroot();
	centerMargin = 20;

	// Cam movement initializations
	direction = 0;
	camSpeed = 700.0f;
	screenMarginV = 20;
	screenMarginH = 20;
    movementMode = false;

	// Cam zoom initializations
	zoomDistanceFromTarget = 750.0f;
	minZoom = 400;
	maxZoom = 1000;
	zoomLevels = 10;
    zoomMode = false;

	// Cam rotation and inclination initializations
	rotSpeed = 2.f;
	inclSpeed = 2.f;

	minInclination = 200.f;
	maxInclination = 260.f;

	delta.x = 0.f;
	delta.y = 230.f;
    rotationOrInclinationMode = false;

	//Center
	centerCameraMode = false;

	//ToDo: deberia actualizarse al redimensionar la pantalla
    screenCenter = Vector2<i32>(w->getInitialWindowWidth()/2, w->getInitialWindowHeight()/2);

	//Set camera and target positions
	tarPos = Vector3<f32>(targetX, targetY, targetZ);
	camPos = tarPos.rotateFromPoint(zoomDistanceFromTarget, delta.x, delta.y);

    camera -> setTargetPosition(tarPos);
	camera -> setCameraPosition(camPos);

	// Set distance to target
	distanceToTarget = camPos.getDistanceTo(tarPos);
}

CameraController::~CameraController() {
	delete camera;
}

void CameraController::Update(f32 deltaTime) {
	tarPos.set(camera -> getTargetPosition());
	camPos.set(camera -> getCameraPosition());

	i32 camHeight = Map::Instance() -> getTerrain() -> getY(camPos.x, camPos.z);

	if (movementMode) {
    	Vector3<f32> camIncr;
		i32 d = delta.x; 
		switch (direction) {
			// up stands for update (delta)
			case 1: //arriba
				camIncr.x = (f32)1;
				camIncr.z = (f32)1;
				d += 0;
			break;
			case 8: //derecha
				camIncr.x = (f32)1;
				camIncr.z = (f32)-1;
				d += 90;
			break;
			case 4: //abajo
				camIncr.x = (f32)-1;
				camIncr.z = (f32)-1;
				d += 180;
			break;
			case 2: // izquierda
				camIncr.x = (f32)-1;
				camIncr.z = (f32)1;
				d += 270;
			break;
			case 9: // arriba derecha
				camIncr.x = (f32)1 * recipsqrt2;
				camIncr.z = (f32)1 * recipsqrt2;
				d+= 45;
			break;
			case 12: //abajo derecha
				camIncr.x = (f32)1 * recipsqrt2;
				camIncr.z = (f32)-1 * recipsqrt2;
				d += 135;
			break;
			case 6: //abajo izquierda
				camIncr.x = (f32)-1 * recipsqrt2;
				camIncr.z = (f32)1 * recipsqrt2;
				d += 225;
			break;
			case 3: // arriba izquierda
				camIncr.x = (f32)1 * recipsqrt2;
				camIncr.z = (f32)1 * recipsqrt2;
				d += 315;
			break;
		}

		camIncr = Vector3<f32>().rotateFromPoint(
			sqrtf(powf(camIncr.x, 2) + powf(camIncr.z, 2)), 
			d,
			0
		) * camSpeed * deltaTime;

		// border collision + apply update
		if (camPos.x < Enumeration::MapMargins::mapMarginTop) {
			if (camIncr.x > 0) {
				camPos.x += camIncr.x;
				tarPos.x += camIncr.x;
			}
		} else if (camPos.x > Enumeration::MapMargins::mapMarginRight) {
			if (camIncr.x < 0) {
				camPos.x += camIncr.x;
				tarPos.x += camIncr.x;
			}
		} else {
			camPos.x += camIncr.x;
			tarPos.x += camIncr.x;
		}

		if (camPos.z < Enumeration::MapMargins::mapMarginTop) {
			if (camIncr.z > 0) {
				camPos.z += camIncr.z;
				tarPos.z += camIncr.z;
			}
		} else if (camPos.z > Enumeration::MapMargins::mapMarginBottom) {
			if (camIncr.z < 0) {
				camPos.z += camIncr.z;
				tarPos.z += camIncr.z;
			}
		} else {
			camPos.z += camIncr.z;
			tarPos.z += camIncr.z;
		}
	}

    if (rotationOrInclinationMode || zoomMode) {
		camPos = tarPos.rotateFromPoint(zoomDistanceFromTarget, delta.x, delta.y);
    }

	if (centerCameraMode){
		std::cout << userPos << std::endl;
		tarPos = userPos;
		camPos = userPos.rotateFromPoint(zoomDistanceFromTarget, delta.x, delta.y);
	}

    if (movementMode || rotationOrInclinationMode || zoomMode || centerCameraMode){
		i32 heightvariance = Map::Instance() -> getTerrain() -> getY(camPos.x, camPos.z) - camHeight;
		camPos.y = camPos.y + heightvariance;

		camera -> setTargetPosition(tarPos.getVectorF());
		camera -> setCameraPosition(camPos.getVectorF());
    }
}

void CameraController::Move() {
	Game *g = Game::Instance();
	Window *w = g->getWindow();

    /*direction = (receiver -> keyDown(KEY_KEY_W) << 0) | (receiver -> keyDown(KEY_KEY_A) << 1)
		| receiver -> keyDown(KEY_KEY_S) << 2 | receiver -> keyDown(KEY_KEY_D) << 3;*/

	direction = 0;
	movementMode = false;

	Vector2<i32> cursorPosCurrent = g -> getMouse() -> getPosition();

	bool cursorOffLimits = false;
	if (cursorPosCurrent.x <= 0) {
		cursorPosCurrent.x = 0;
		cursorOffLimits = true;
	} else if (cursorPosCurrent.x >= w -> getRealWindowWidth()) {
		cursorPosCurrent.x = w -> getRealWindowWidth();
		cursorOffLimits = true;
	}

	if (cursorPosCurrent.y <= 0) {
		cursorPosCurrent.y = 0;
		cursorOffLimits = true;
	} else if (cursorPosCurrent.y >= w -> getRealWindowHeight()) {
		cursorPosCurrent.y = w -> getRealWindowHeight();
		cursorOffLimits = true;
	}

	if (cursorOffLimits) g -> getMouse() -> setPosition(cursorPosCurrent);
	
	if (cursorPosCurrent.y < screenMarginV) {
		direction |= 1 << 0;
        movementMode = true;
	} else if (cursorPosCurrent.y > (w -> getRealWindowHeight() - screenMarginV)) {
		direction |= 1 << 2;
        movementMode = true;
	}

	if (cursorPosCurrent.x < screenMarginH) {
		direction |= 1 << 1;
        movementMode = true;
	} else if (cursorPosCurrent.x > (w -> getRealWindowWidth() - screenMarginH)) {
		direction |= 1 << 3;
        movementMode = true;
	}
}

void CameraController::Zoom(){
	Game *g = Game::Instance();

	zoomMode = false;

	if (g -> getMouse() -> getWheelY() > 0.0f) {
		if (zoomDistanceFromTarget > minZoom) {
			Vector3<f32> incr = distanceToTarget / zoomLevels;
			zoomDistanceFromTarget -= incr.y;

			camSpeed += sqrt(zoomLevels);

			zoomMode = true;
		}
	} else if (g -> getMouse() -> getWheelY() < 0.0f) {
		if (zoomDistanceFromTarget < maxZoom) {
			Vector3<f32> incr = distanceToTarget / zoomLevels;
			zoomDistanceFromTarget += incr.y;

			camSpeed -= sqrt(zoomLevels);

			zoomMode = true;
		}
	}
}

void CameraController::RotateAndInclinate(){
	Game *g = Game::Instance();

    // If mouse button pressed
    if (g -> getMouse() -> middleMousePressed()) {
		// get cursor data
        cursorPosSaved = g -> getMouse() -> getPosition();
        g -> getMouse() -> setPosition(screenCenter);

		Game::Instance() -> getMouse() -> hide();

        rotationOrInclinationMode = true;
    } else if (g -> getMouse() -> middleMouseReleased()) {
        g -> getMouse() -> setPosition(cursorPosSaved);
		
		Game::Instance() -> getMouse() -> show();

        rotationOrInclinationMode = false;
    }

	if (rotationOrInclinationMode) {
		Vector2<i32> cursorPosCurrent = g -> getMouse() -> getPosition();

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
        g -> getMouse() -> setPosition(screenCenter.getVectorF()); 

		// refresh distance to target
		distanceToTarget = camPos.getDistanceTo(tarPos);
	}
}

void CameraController::CenterCamera(){
	Game *g = Game::Instance();

	centerCameraMode = false;
	if (g -> getKeyboard() -> keyPressed(GLFW_KEY_SPACE)) { //ToDo: fachada
		if(Human::Instance() -> getUnitManager() -> getSelectedTroop() != NULL) {
			userPos.x = Human::Instance() -> getUnitManager() -> getSelectedTroop() -> getPosition() -> x;
			userPos.z = Human::Instance() -> getUnitManager() -> getSelectedTroop() -> getPosition() -> z;
			userPos.y = Map::Instance() -> getTerrain() -> getY(userPos.x, userPos.z);
		} else {
			userPos.x = Human::Instance() -> getHallPosition().x;
			userPos.y = Human::Instance() -> getHallPosition().y;
			userPos.z = Human::Instance() -> getHallPosition().z;
		}
		centerCameraMode = true;
	}
}

Camera *CameraController::getCamera() {
	return camera;
}