#pragma once
#include "core/vector2.h"
#include "core/drawing.h"
#include "core/configuration.h"
#include "core/input.h"
#include "wall.h"

class FirstPerson {
private:
	Vector2* cameraPosition;
	float* cameraAngle;

	void drawWall(Wall wall);
	void iterateBSPTree(WallNode *node);
public:
	FirstPerson();
	FirstPerson(Vector2* cameraPosition, float* cameraAngle);

	void update();
	void draw(Wall* wallArray, int wallCount);
	void drawUsingBSP(WallNode *rootNode);
};