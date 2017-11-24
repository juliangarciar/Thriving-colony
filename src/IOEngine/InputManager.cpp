#include "InputManager.h"

InputManager::InputManager() {
	wheel[0] = false;
	wheel[1] = false;
	for (u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i)
		KeyIsDown[i] = false;
}

InputManager::~InputManager() {
    
}

bool InputManager::OnEvent(const SEvent& event) {
	if (event.EventType == EET_MOUSE_INPUT_EVENT) {
		if (event.MouseInput.isLeftPressed())
			MouseDown[0] = true;
		else
			MouseDown[0] = false;

		if (event.MouseInput.isRightPressed())
			MouseDown[1] = true;
		else
			MouseDown[1] = false;
	}

	if (event.MouseInput.Event == EMIE_MOUSE_WHEEL) {
		wheel[0] = true;
		wheel[1] = event.MouseInput.Wheel > 0;
	}

	if (event.EventType == irr::EET_KEY_INPUT_EVENT)
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

	return false;
}

bool InputManager::IsKeyDown(EKEY_CODE keyCode) const {
	return KeyIsDown[keyCode];
}

bool InputManager::isMouseLDown() const {
	return MouseDown[0];
}

bool InputManager::isMouseRDown() const {
	return MouseDown[1];
}

bool InputManager::isWheelUp() const {
	return wheel[1];
}

bool InputManager::getWheelState() const {
	return wheel[0];
}

void InputManager::setWheelState(bool wheel1) {
	wheel[0] = wheel1;
}