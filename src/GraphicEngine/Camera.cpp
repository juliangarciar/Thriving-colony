#include "Camera.h"

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

void Camera::Move(Input *receiver) {
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

	core::position2d<s32> cursorPosCurrent = receiver->getCursor()->getPosition();
	if (cursorPosCurrent.Y < 1)
		n |= 1 << 0;
	else if (cursorPosCurrent.Y > (sc->getScreenWidth() - 20))
		n |= 1 << 2;
	if (cursorPosCurrent.X < 1)
		n |= 1 << 1;
	else if (cursorPosCurrent.X > (sc->getScreenWidth() - 20))
		n |= 1 << 3;

	// =========================================================================
/*	camPos = camera->getPosition();
	camTar1 = camera->getTarget();

	if (n != 0)
	{
		switch (n)
		{
			// up stands for update (delta)
		case 1:
			Xup = (f32)camSpeed * *deltaTime * direction.X;
			Yup = (f32)camSpeed * *deltaTime * direction.Y;
			break;
		case 2:
			Xup = (f32)-camSpeed * *deltaTime*direction.Y;
			Yup = (f32)camSpeed * *deltaTime*direction.X;
			break;
		case 8:
			Xup = (f32)camSpeed * *deltaTime*direction.Y;
			Yup = (f32)-camSpeed * *deltaTime*direction.X;
			break;
		case 4:
			Xup = (f32)-camSpeed * *deltaTime * direction.X;
			Yup = (f32)-camSpeed * *deltaTime * direction.Y;
			break;
		case 3:
			Xup = (f32)camSpeed * *deltaTime * (-direction.Y + direction.X) * recipsqrt2;
			Yup = (f32)camSpeed * *deltaTime * (direction.X + direction.Y) * recipsqrt2;
			break;
		case 9:
			Xup = (f32)camSpeed * *deltaTime * (direction.Y + direction.X) * recipsqrt2;
			Yup = (f32)camSpeed * *deltaTime * (-direction.X + direction.Y) * recipsqrt2;
			break;
		case 6:
			Xup = (f32)-camSpeed * *deltaTime * (direction.Y + direction.X) * recipsqrt2;
			Yup = (f32)camSpeed * *deltaTime * (direction.X - direction.Y) * recipsqrt2;
			break;
		case 12:
			Xup = camSpeed * *deltaTime * (direction.Y - direction.X) * recipsqrt2;
			Yup = -camSpeed * *deltaTime * (direction.X + direction.Y) * recipsqrt2;
			break;
		}

		// border collision + apply update
		if (camPos.X < 100)
		{
			if (Xup > 0)
			{
				camPos.X += Xup;
				camTar1.X += Xup;
			}
		}
		else if (camPos.X > 924)
		{
			if (Xup < 0)
			{
				camPos.X += Xup;
				camTar1.X += Xup;
			}
		}
		else
		{
			camPos.X += Xup;
			camTar1.X += Xup;
		}

		if (camPos.Z < 100)
		{
			if (Yup > 0)
			{
				camPos.Z += Yup;
				camTar1.Z += Yup;
			}
		}
		else if (camPos.Z > 924)
		{
			if (Yup < 0)
			{
				camPos.Z += Yup;
				camTar1.Z += Yup;
			}
		}
		else
		{
			camPos.Z += Yup;
			camTar1.Z += Yup;
		}
	}

	currentHight = terrain->getHeight(camPos.X, camPos.Z);
	camPos.Y = 0.85f*camPos.Y + 0.15f*(currentHight + camHeight);
	camTar1.Y = 0.85f*camTar1.Y + 0.15f*(currentHight + tarHeight);
    
	camera->setPosition(camPos);
	camera->setTarget(camTar1);*/
}