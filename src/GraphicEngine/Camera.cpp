#include "Camera.h"
#include "Screen.h"

using namespace irr;

Camera::Camera(scene::ISceneManager* sceneManager) {
    camera = sceneManager->addCameraSceneNode(0);
	recipsqrt2 = core::reciprocal_squareroot((f32)2);
	direction.x = camera->getTarget().X - camera->getPosition().X;
	direction.y = camera->getTarget().Z - camera->getPosition().Z;
	//direction.normalize();
	camSpeed = 10.f;
	camHeight = 200.f;
	tarHeight = 160.f;
	minZoom = 150;
	maxZoom = 400;
	marginTop = 20;
	marginLeft = 30;
	mapMarginTop = 100;
	mapMarginLeft = 100;
	mapMarginBottom = 9240;
	mapMarginRight = 9240;
	inclination.setPosition(100,100);
}

Camera::~Camera() {
    delete camera;
    camera = NULL;
}

//Posicion de la camara
void Camera::setPosition(Vector3<float> position){
	camPos = position;
    camera->setPosition(camPos.getVectorF());
    camera->setTarget(core::vector3df(camPos.x+inclination.x, 0, camPos.z+inclination.y)); //ToDo: Mas inclinacion
	direction.x = camera->getTarget().X - camera->getPosition().X;
	direction.y = camera->getTarget().Z - camera->getPosition().Z;
}

//Hacia donde apunta la camara
void Camera::setInclination(Vector2<float> inclination){
	this->inclination = inclination;
	this->setPosition(this->camPos);
}

void Camera::setShadowDistance(float zoom){
	camera->setFarValue(zoom);
}

void Camera::Move(InputManager *receiver, Mouse *cursor, Terrain *terrain) {
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

	int n = (receiver->IsKeyDown(KEY_KEY_W) << 0) | (receiver->IsKeyDown(KEY_KEY_A) << 1)
		| receiver->IsKeyDown(KEY_KEY_S) << 2 | receiver->IsKeyDown(KEY_KEY_D) << 3;

	core::position2d<s32> cursorPosCurrent = cursor->getCursor()->getPosition();
	
	if (cursorPosCurrent.Y < marginTop){
		n |= 1 << 0;
	} else if (cursorPosCurrent.Y > (sc->getScreenHeight() - marginTop)) {
		n |= 1 << 2;
	}

	if (cursorPosCurrent.X < marginLeft){
		n |= 1 << 1;
	} else if (cursorPosCurrent.X > (sc->getScreenWidth() - marginLeft)) {
		n |= 1 << 3;
	}

	// =========================================================================
	camPos.setPosition(camera->getPosition());
	camTar1.setPosition(camera->getTarget());

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
			}
		} else if (camPos.x > mapMarginRight){
			if (Xup < 0) {
				camPos.x += Xup;
				camTar1.x += Xup;
			}
		} else {
			camPos.x += Xup;
			camTar1.x += Xup;
		}

		if (camPos.z < mapMarginTop) {
			if (Yup > 0) {
				camPos.z += Yup;
				camTar1.z += Yup;
			}
		} else if (camPos.z > mapMarginBottom) {
			if (Yup < 0) {
				camPos.z += Yup;
				camTar1.z += Yup;
			}
		} else {
			camPos.z += Yup;
			camTar1.z += Yup;
		}
	}

	currentHeight = terrain->getTerrain()->getHeight(camPos.x, camPos.z);

	camPos.y = 0.85f*camPos.y + 0.15f*(currentHeight + camHeight);

	//ToDo: revisar zoom
	//camTar1.y = 0.85f*camTar1.y + 0.15f*(currentHeight + tarHeight);
    
	camera->setPosition(camPos.getVectorF());
	camera->setTarget(camTar1.getVectorF());
}