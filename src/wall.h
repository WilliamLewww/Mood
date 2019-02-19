#pragma once
#include "core/vector2.h"

struct Wall {
	Vector2 pointA;
	Vector2 pointB;
	int color[3] = { 255, 0, 0 };
};