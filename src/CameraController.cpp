#include "CameraController.h"

#include "Human.h"
#include "IA.h"
#include "Map.h"
#include "IOEngine/IO.h"
#include "GraphicEngine/Window.h"

//ToDo: llevarse datos a JSON
CameraController::CameraController() {
	Window *w = Window::Instance();

	//Camera 
    camera = new Camera();
    camera -> setFarValue(42000.f);

	// Helper initializations
	recipsqrt2 = 1.0 / sqrt(2);
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

	rotateDegrees.x = 0.f;
	rotateDegrees.y = 230.f;
    rotationOrInclinationMode = false;

	//Center
	centerCameraMode = false;

	//ToDo: deberia actualizarse al redimensionar la pantalla
    screenCenter = Vector2<i32>(w->getInitialWindowWidth()/2, w->getInitialWindowHeight()/2);

	i32 framesPerSecond = 60;
	updateTimer = new Timer(1/framesPerSecond, true, false);

	updateTimer -> setCallback([&](){
        updateCamera(Window::Instance() -> getDeltaTime());
	});
}

CameraController::~CameraController() {
	delete camera;
	delete updateTimer;
}

void CameraController::Init(Vector3<f32> v){
	//Set camera and target positions
	tarPos = v;
	camPos = tarPos.rotateFromPoint(zoomDistanceFromTarget, rotateDegrees.x, rotateDegrees.y);

    camera -> setTargetPosition(tarPos);
	camera -> setCameraPosition(camPos);

	// Set distance to target
	distanceToTarget = camPos.getDistanceTo(tarPos);

	updateTimer -> start();
}

void CameraController::Update() {
	updateTimer -> tick();
}

void CameraController::updateCamera(f32 deltaTime) {
	if (movementMode) {
    	Vector3<f32> tarIncr;
		i32 d = rotateDegrees.x; 
		switch (direction) {
			// up stands for update (delta)
			case 1: //arriba
				tarIncr.x = (f32)1;
				tarIncr.z = (f32)1;
				d += 0;
			break;
			case 8: //derecha
				tarIncr.x = (f32)1;
				tarIncr.z = (f32)-1;
				d += 90;
			break;
			case 4: //abajo
				tarIncr.x = (f32)-1;
				tarIncr.z = (f32)-1;
				d += 180;
			break;
			case 2: // izquierda
				tarIncr.x = (f32)-1;
				tarIncr.z = (f32)1;
				d += 270;
			break;
			case 9: // arriba derecha
				tarIncr.x = (f32)1 * recipsqrt2;
				tarIncr.z = (f32)1 * recipsqrt2;
				d+= 45;
			break;
			case 12: //abajo derecha
				tarIncr.x = (f32)1 * recipsqrt2;
				tarIncr.z = (f32)-1 * recipsqrt2;
				d += 135;
			break;
			case 6: //abajo izquierda
				tarIncr.x = (f32)-1 * recipsqrt2;
				tarIncr.z = (f32)1 * recipsqrt2;
				d += 225;
			break;
			case 3: // arriba izquierda
				tarIncr.x = (f32)1 * recipsqrt2;
				tarIncr.z = (f32)1 * recipsqrt2;
				d += 315;
			break;
		}

		tarIncr = Vector3<f32>().rotateFromPoint(
			sqrtf(powf(tarIncr.x, 2) + powf(tarIncr.z, 2)), 
			d,
			0
		) * camSpeed * deltaTime;

		// border collision + apply update
		if (tarPos.x < Enumeration::MapMargins::mapMarginTop) {
			if (tarIncr.x > 0) tarPos.x += tarIncr.x;
		} else if (tarPos.x > Enumeration::MapMargins::mapMarginRight) {
			if (tarIncr.x < 0) tarPos.x += tarIncr.x;
		} else {
			tarPos.x += tarIncr.x;
		}

		if (tarPos.z < Enumeration::MapMargins::mapMarginTop) {
			if (tarIncr.z > 0) tarPos.z += tarIncr.z;
		} else if (tarPos.z > Enumeration::MapMargins::mapMarginBottom) {
			if (tarIncr.z < 0) tarPos.z += tarIncr.z;
		} else {
			tarPos.z += tarIncr.z;
		}
	}

	if (centerCameraMode){
		tarPos = userPos;
	}

    if (movementMode || rotationOrInclinationMode || zoomMode || centerCameraMode){
		tarPos.y = Map::Instance() -> getTerrain() -> getY(tarPos.x, tarPos.z);
		camPos = tarPos.rotateFromPoint(zoomDistanceFromTarget, rotateDegrees.x, rotateDegrees.y);

		i32 camHeight = camPos.y - tarPos.y;
		i32 mapHeight = Map::Instance() -> getTerrain() -> getY(camPos.x, camPos.z);

		camPos.y = mapHeight + camHeight;

		camera -> setTargetPosition(tarPos);
		camera -> setCameraPosition(camPos);
    }
}

void CameraController::Move() {
	Window *w = Window::Instance();

	direction = 0;
	movementMode = false;

	Vector2<i32> cursorPosCurrent = IO::Instance() -> getMouse() -> getPosition();

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

	if (cursorOffLimits) IO::Instance() -> getMouse() -> setPosition(cursorPosCurrent);
	
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
	zoomMode = false;

	if (IO::Instance() -> getMouse() -> getWheelY() > 0.0f) {
		if (zoomDistanceFromTarget > minZoom) {
			Vector3<f32> incr = distanceToTarget / zoomLevels;
			zoomDistanceFromTarget -= incr.y;

			camSpeed += sqrt(zoomLevels);

			zoomMode = true;
		}
	} else if (IO::Instance() -> getMouse() -> getWheelY() < 0.0f) {
		if (zoomDistanceFromTarget < maxZoom) {
			Vector3<f32> incr = distanceToTarget / zoomLevels;
			zoomDistanceFromTarget += incr.y;

			camSpeed -= sqrt(zoomLevels);

			zoomMode = true;
		}
	}
}

void CameraController::RotateAndInclinate(){
    // If mouse button pressed
    if (IO::Instance() -> getMouse() -> middleMousePressed()) {
		// get cursor data
        cursorPosSaved = IO::Instance() -> getMouse() -> getPosition();
        IO::Instance() -> getMouse() -> setPosition(screenCenter);

		IO::Instance() -> getMouse() -> hide();

        rotationOrInclinationMode = true;
    } else if (IO::Instance() -> getMouse() -> middleMouseReleased()) {
        IO::Instance() -> getMouse() -> setPosition(cursorPosSaved);
		
		IO::Instance() -> getMouse() -> show();

        rotationOrInclinationMode = false;
    }

	if (rotationOrInclinationMode) {
		Vector2<i32> cursorPosCurrent = IO::Instance() -> getMouse() -> getPosition();

		//Increase or decease rotation angle
		if (cursorPosCurrent.x < screenCenter.x - centerMargin) {
			rotateDegrees.x += rotSpeed;
		} else if (cursorPosCurrent.x > screenCenter.x + centerMargin) {
			rotateDegrees.x -= rotSpeed;
		}

		//Increase or decease inclination angle
		if (cursorPosCurrent.y < screenCenter.y - centerMargin) {
			rotateDegrees.y += inclSpeed;
		} else if (cursorPosCurrent.y > screenCenter.y + centerMargin) {
			rotateDegrees.y -= inclSpeed;
		}

        // fix if they are offlimits
        rotateDegrees.x = (rotateDegrees.x < 0) ? 360+rotateDegrees.x : rotateDegrees.x;
        rotateDegrees.x = (rotateDegrees.x > 360) ? rotateDegrees.x-360 : rotateDegrees.x;

        // fix if they are offlimits
        rotateDegrees.y = (rotateDegrees.y < minInclination) ? minInclination : rotateDegrees.y;
        rotateDegrees.y = (rotateDegrees.y > maxInclination) ? maxInclination : rotateDegrees.y;

        // reset cursor position to center
        IO::Instance() -> getMouse() -> setPosition(screenCenter); 

		// refresh distance to target
		distanceToTarget = camPos.getDistanceTo(tarPos);
	}
}

void CameraController::CenterCamera(){
	centerCameraMode = false;
	if (IO::Instance() -> getKeyboard() -> keyPressed(GLFW_KEY_SPACE)) { //ToDo: fachada
		if(Human::Instance() -> getUnitManager() -> getSelectedTroop() != nullptr) {
			userPos.x = Human::Instance() -> getUnitManager() -> getSelectedTroop() -> getPosition() . x;
			userPos.z = Human::Instance() -> getUnitManager() -> getSelectedTroop() -> getPosition() . y;
			userPos.y = Map::Instance() -> getTerrain() -> getY(userPos.x, userPos.z);
		} else {
			userPos.x = Human::Instance() -> getHallPosition().x;
			userPos.z = Human::Instance() -> getHallPosition().y;
			userPos.y = Map::Instance() -> getTerrain() -> getY(userPos.x, userPos.z);
		}
		centerCameraMode = true;
	}
}

Camera *CameraController::getCamera() {
	return camera;
}

void CameraController::setZoomDistanceFromTarget(i32 zoom){
	zoomDistanceFromTarget = zoom;
}

void CameraController::setRotateDegrees(i32 x, i32 y){
	rotateDegrees.x = x;
	rotateDegrees.y = y; 
}

Vector3<f32> CameraController::getTargetPosition() {
	return tarPos;
}

Vector3<f32> CameraController::getCameraPosition() {
	return camPos;
}