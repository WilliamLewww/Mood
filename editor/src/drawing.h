#pragma once
#include <SDL2\SDL_opengl.h>
#include <SDL2\SDL_ttf.h>
#include "vector2.h"

class Drawing {
private:
	double convertColorFloatToRGB(int rgbValue);
public:
	void drawLine(Vector2 a, Vector2 b, int color[3]);
	void drawRect(Vector2 position, int width, int height, int color[3]);
};

extern Drawing drawing;