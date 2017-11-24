#include "Camera.h"
#include "Screen.h"

using namespace irr;

Camera::Camera(scene::ISceneManager* sceneManager) {
    camera = sceneManager->addCameraSceneNode(0);
}

Camera::~Camera() {
    delete camera;
    camera = NULL;
}

//Posicion de la camara
void Camera::setPosition(Vector3<float> position){
    camera->setPosition(position.getVectorF());
}

//Hacia donde apunta la camara
void Camera::setTargetPosition(Vector3<float> position){
    camera->setTarget(position.getVectorF());
}

void Camera::setShadowDistance(float zoom){
	camera->setFarValue(zoom);
}

void Camera::Move(InputManager *receiver, Mouse *mouse, Terrain *terrain) {
	Screen *sc = Screen::Instance();
	if (receiver->getWheelState()) {
		receiver->setWheelState(false);
		if (receiver->isWheelUp()) {
			if (camHeight > 50) {
				camHeight -= 20.0f;
				tarHeight -= 20.0f;
				camSpeed -= 0.02f;
			}
		} else {
			if (camHeight < 210) {
				camHeight += 20.0f;
				tarHeight += 20.0f;
				camSpeed += 0.02f;
			}
		}
	}

	int n = (receiver->IsKeyDown(KEY_KEY_W) << 0) | (receiver->IsKeyDown(KEY_KEY_A) << 1)
		| receiver->IsKeyDown(KEY_KEY_S) << 2 | receiver->IsKeyDown(KEY_KEY_D) << 3;

	core::position2d<s32> cursorPosCurrent = mouse->getCursor()->getPosition();
	if (cursorPosCurrent.Y < 1)
		n |= 1 << 0;
	else if (cursorPosCurrent.Y > (sc->getScreenWidth() - 20))
		n |= 1 << 2;
	if (cursorPosCurrent.X < 1)
		n |= 1 << 1;
	else if (cursorPosCurrent.X > (sc->getScreenWidth() - 20))
		n |= 1 << 3;

	// =========================================================================
	camPos.setPosition(camera->getPosition());
	camTar1.setPosition(camera->getTarget());

	if (n != 0)
	{
		switch (n)
		{
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
		if (camPos.x < 100)
		{
			if (Xup > 0)
			{
				camPos.x += Xup;
				camTar1.x += Xup;
			}
		}
		else if (camPos.x > 924)
		{
			if (Xup < 0)
			{
				camPos.x += Xup;
				camTar1.x += Xup;
			}
		}
		else
		{
			camPos.x += Xup;
			camTar1.x += Xup;
		}

		if (camPos.z < 100)
		{
			if (Yup > 0)
			{
				camPos.z += Yup;
				camTar1.z += Yup;
			}
		}
		else if (camPos.z > 924)
		{
			if (Yup < 0)
			{
				camPos.z += Yup;
				camTar1.z += Yup;
			}
		}
		else
		{
			camPos.z += Yup;
			camTar1.z += Yup;
		}
	}

	currentHight = terrain->getTerrain()->getHeight(camPos.x, camPos.z);
	camPos.y = 0.85f*camPos.y + 0.15f*(currentHight + camHeight);
	camTar1.y = 0.85f*camTar1.y + 0.15f*(currentHight + tarHeight);
    
	camera->setPosition(camPos.getVectorF());
	camera->setTarget(camTar1.getVectorF());
}