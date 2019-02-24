#pragma once
#include <vector>
#include <algorithm>
#include <SDL2\SDL.h>

class Input {
private:
	std::vector<SDL_Keycode> keyList;
	bool backspacePress = false;
	bool returnPress = false;
	int mouseX, mouseY;
	bool leftClickPress = false;
	bool rightClickPress = false;
public:
	void refreshInput();
	void getTrigger(SDL_Event event);

	bool checkKeyDown(SDL_Keycode Keycode);

	inline int getMouseX() { return mouseX; };
	inline int getMouseY() { return mouseY; };

	inline bool checkBackspacePress() { return backspacePress; };
	inline bool checkReturnPress() { return returnPress; };
	inline bool checkLeftClickPress() { return leftClickPress; };
	inline bool checkRightClickPress() { return rightClickPress; };
};

extern Input input;