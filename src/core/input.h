#pragma once
#include <vector>
#include <algorithm>
#include <SDL2\SDL.h>
#include "vector2.h"
#include "configuration.h"

class Input {
private:
	std::vector<SDL_Keycode> keyList;
	std::vector<SDL_Keycode> pressKeyList;

	bool leftButtonDown, leftButtonPress;
	bool rightButtonDown, rightButtonPress;
	bool middleMouseDown, middleMousePress;
	bool scrollUp, scrollDown;
	int mouseX, mouseY;

	int controllerPad;
	std::vector<int> controllerList;
	std::vector<int> controllerPressList;

	Vector2* cameraPosition;
public:
	inline void linkCamera(Vector2* cameraPosition) { this->cameraPosition = cameraPosition; };

	std::vector<SDL_Keycode> returnKeyList();

	inline int getMouseX() { return mouseX; };
	inline int getMouseY() { return mouseY; };
	inline int getMouseXCamera() { return cameraPosition->x + mouseX; };
	inline int getMouseYCamera() { return cameraPosition->y + mouseY; };

	inline Vector2 getMouse() { return Vector2(mouseX, mouseY); }
	inline Vector2 getMouseCamera() { return Vector2(cameraPosition->x + mouseX, cameraPosition->y + mouseY); }
	
	inline bool getLeftButtonPress() { return leftButtonPress; };
	inline bool getRightButtonPress() { return rightButtonPress; };

	inline bool getScrollUp() { return scrollUp; };
	inline bool getScrollDown() { return scrollDown; };
	
	bool checkKeyDown(SDL_Keycode Keycode);
	bool checkKeyPress(SDL_Keycode Keycode);
	bool checkButtonDown(int buttonCode);
	int getControllerPadInput();
	int getKeyListSize();
	int getPressKeyListSize();

	void getKeyTrigger(SDL_Event event);
	void clearExpiredInput();
	void getMouseTrigger(SDL_Event event);
	void setupController();
	bool checkMouseOnEntity(Vector2 entityPosition, int entityWidth, int entityHeight);
};

extern Input input;