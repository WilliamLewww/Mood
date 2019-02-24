#pragma once
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <algorithm>
#include "core/vector2.h"

enum WallPosition { WALL_FRONT, WALL_BACK };

struct Wall {
	Vector2 pointA;
	Vector2 pointB;
	int color[3] = { 255, 0, 0 };
};

struct WallNode {
	Wall splitter;

	WallNode* left = nullptr;
	WallNode* right = nullptr;
};

void printTree(WallNode* root, const std::string& prefix);
std::ostream &operator<<(std::ostream &os, Wall const &wall);
WallNode* readBinaryTree(WallNode *node, std::ifstream &fin);
WallPosition getWallPosition(Wall parentWall, Wall wall);
WallPosition getWallPosition(Wall parentWall, Vector2 point);