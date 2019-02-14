#pragma once
#include "core/vector2.h"
#include "core/drawing.h"
#include "core/configuration.h"
#include "wall.h"

class FirstPerson {
private:
	Vector2* cameraPosition;
	float* cameraAngle;

	void drawWall(Wall wall);
public:
	FirstPerson();
	FirstPerson(Vector2* cameraPosition, float* cameraAngle);

	void draw(Wall* wallArray, int wallCount);
};