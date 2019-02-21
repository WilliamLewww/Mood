#include "input.h"

Input input;

void Input::refreshInput() {
	backspacePress = false;
	returnPress = false;
	leftClickPress = false;
	rightClickPress = false;
	generateBMPPress = false;
}

void Input::getTrigger(SDL_Event event) {
	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) { leftClickPress = true; }
	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_RIGHT) { rightClickPress = true; }
	if (event.type == SDL_MOUSEMOTION) {
		mouseX = event.motion.x;
		mouseY = event.motion.y;
	}
	if (event.type == SDL_KEYDOWN) {
		if (std::find(keyList.begin(), keyList.end(), event.key.keysym.sym) == keyList.end()) {
			if (event.key.keysym.sym == SDLK_RETURN) {  returnPress = true; }
			else {
				if (event.key.keysym.sym == SDLK_BACKSPACE) { backspacePress = true; }
				else {
					if (event.key.keysym.sym == SDLK_b) { generateBMPPress = true; }
					else { keyList.push_back(event.key.keysym.sym); }
				}
			}
		}
	}
	if (event.type == SDL_KEYUP) {
		keyList.erase(std::remove(keyList.begin(), keyList.end(), event.key.keysym.sym), keyList.end());
	}
}

bool Input::checkKeyDown(SDL_Keycode Keycode) {
	if (std::find(keyList.begin(), keyList.end(), Keycode) != keyList.end()) {
		return true;
	}

	return false;
}