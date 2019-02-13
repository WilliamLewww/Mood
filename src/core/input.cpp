#include "input.h"

Input input;

std::vector<SDL_Keycode> Input::returnKeyList() {
	return keyList;
}

int Input::getKeyListSize() {
	return keyList.size();
}

int Input::getPressKeyListSize() {
	return pressKeyList.size();
}

bool Input::checkKeyDown(SDL_Keycode Keycode) {
	if (std::find(keyList.begin(), keyList.end(), Keycode) != keyList.end()) {
		return true;
	}

	return false;
}

bool Input::checkKeyPress(SDL_Keycode Keycode) {
	if (std::find(pressKeyList.begin(), pressKeyList.end(), Keycode) != pressKeyList.end()) {
		return true;
	}

	return false;
}

bool Input::checkButtonDown(int buttonCode) {
	if (std::find(controllerList.begin(), controllerList.end(), buttonCode) != controllerList.end()) {
		return true;
	}

	return false;
}

int Input::getControllerPadInput() {
	return controllerPad;
}

void Input::setupController() {
	if (SDL_NumJoysticks() > 0) {
		SDL_JoystickOpen(0);
	}
}

void Input::getKeyTrigger(SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		if (std::find(keyList.begin(), keyList.end(), event.key.keysym.sym) == keyList.end()) {
			pressKeyList.push_back(event.key.keysym.sym);
			keyList.push_back(event.key.keysym.sym);
		}
	}

	if (event.type == SDL_KEYUP) {
		keyList.erase(std::remove(keyList.begin(), keyList.end(), event.key.keysym.sym), keyList.end());
	}

	if (event.type == SDL_JOYHATMOTION) {
		switch (event.jhat.value) {
			case SDL_HAT_UP: controllerPad = 1; break;
			case SDL_HAT_RIGHTUP: controllerPad = 2; break;
			case SDL_HAT_RIGHT: controllerPad = 3; break;
			case SDL_HAT_RIGHTDOWN: controllerPad = 4; break;
			case SDL_HAT_DOWN: controllerPad = 5; break;
			case SDL_HAT_LEFTDOWN: controllerPad = 6; break;
			case SDL_HAT_LEFT: controllerPad = 7; break;
			case SDL_HAT_LEFTUP: controllerPad = 8; break;
			case SDL_HAT_CENTERED: controllerPad = 0; break;
			default: break;
		}
	}

	if (event.type == SDL_JOYBUTTONDOWN) {
		if (std::find(controllerList.begin(), controllerList.end(), event.jbutton.button) == controllerList.end()) {
			controllerPressList.push_back(event.jbutton.button);
			controllerList.push_back(event.jbutton.button);
		}
	}

	if (event.type == SDL_JOYBUTTONUP) {
		controllerList.erase(std::remove(controllerList.begin(), controllerList.end(), event.jbutton.button), controllerList.end());
	}
}

void Input::clearExpiredInput() {
	pressKeyList.clear();
	controllerPressList.clear();

	leftButtonPress = false;
	rightButtonPress = false;
	middleMousePress = false;
	scrollUp = false;
	scrollDown = false;
}

void Input::getMouseTrigger(SDL_Event event) {
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (event.button.button == SDL_BUTTON_LEFT) {
			leftButtonDown = true;
			leftButtonPress = true;
		}

		if (event.button.button == SDL_BUTTON_RIGHT) {
			rightButtonDown = true;
			rightButtonPress = true;
		}

		if (event.button.button == SDL_BUTTON_MIDDLE) {
			middleMouseDown = true;
			middleMousePress = true;
		}
	}

	if (event.type == SDL_MOUSEWHEEL) {
		if (event.wheel.y > 0) {
			scrollUp = true;
		}
		else {
			scrollDown = true;
		}
	}

	if (event.type == SDL_MOUSEBUTTONUP) {
		if (event.button.button == SDL_BUTTON_LEFT) {
			leftButtonDown = false;
		}

		if (event.button.button == SDL_BUTTON_RIGHT) {
			rightButtonDown = false;
		}

		if (event.button.button == SDL_BUTTON_MIDDLE) {
			middleMouseDown = false;
		}
	}

	if (event.type == SDL_MOUSEMOTION) {
		mouseX = event.motion.x;
		mouseY = event.motion.y;
	}
}

bool Input::checkMouseOnEntity(Vector2 entityPosition, int entityWidth, int entityHeight) {
	if (mouseX >= entityPosition.x && mouseX <= entityPosition.x + entityWidth && mouseY >= entityPosition.y && mouseY <= entityPosition.y + entityHeight) {
		return true;
	}

	return false;
}