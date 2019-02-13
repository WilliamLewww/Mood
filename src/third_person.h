#pragma once
#include "core/vector2.h"
#include "core/drawing.h"
#include "core/configuration.h"
#include "wall.h"

class ThirdPerson {
private:
	Vector2* cameraPosition;
	float* cameraAngle;
public:
	ThirdPerson();
	ThirdPerson(Vector2* cameraPosition, float* cameraAngle);

	void draw(Wall* wallArray, int wallCount);
};