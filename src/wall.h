#pragma once
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <algorithm>
#include "core/vector2.h"

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

std::ostream &operator<<(std::ostream &os, Wall const &wall);
void printTree(WallNode* root, const std::string& prefix);
WallNode* readBinaryTree(WallNode *node, std::ifstream &fin);