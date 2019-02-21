#include "drawing.h"

Drawing drawing;

double Drawing::convertColorFloatToRGB(int rgbValue) {
	return (double)rgbValue / 255;
}

void Drawing::drawLine(Vector2 a, Vector2 b, int color[3]) {
	glBegin(GL_LINES);
	glColor4f(convertColorFloatToRGB(color[0]), convertColorFloatToRGB(color[1]), convertColorFloatToRGB(color[2]), 1);
	glVertex2f(a.x - 350.0, a.y - 350.0);
	glVertex2f(b.x - 350.0, b.y - 350.0);
	glEnd();
}

void Drawing::drawRect(Vector2 position, int width, int height, int color[3]) {
	Vector2 vectors[4]{
		{0, 0},
		{1, 0},
		{1, 1},
		{0, 1}
	};

	glBegin(GL_QUADS);
	glColor4f(convertColorFloatToRGB(color[0]), convertColorFloatToRGB(color[1]), convertColorFloatToRGB(color[2]), 1);
	for (int x = 0; x < 4; x++) {
		vectors[x].x *= width;
		vectors[x].y *= height;
		vectors[x].x += position.x;
		vectors[x].y += position.y;
		vectors[x].x -= 350.0;
		vectors[x].y -= 350.0;

		glVertex2d(vectors[x].x, vectors[x].y);
	}
	glEnd();
}