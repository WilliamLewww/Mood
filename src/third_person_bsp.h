#pragma once
#include "core/vector2.h"
#include "core/drawing.h"
#include "core/configuration.h"
#include "wall.h"

class ThirdPersonBSP {
private:
	Vector2* cameraPosition;
	float* cameraAngle;

	void drawWall(Wall wall, int colorA);
	void iterateBSPTree(WallNode *node, int colorA);
public:
	ThirdPersonBSP();
	ThirdPersonBSP(Vector2* cameraPosition, float* cameraAngle);

	void draw(WallNode *rootNode);
};