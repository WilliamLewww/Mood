#pragma once
#include <iostream>
#include <cmath>
#include <fstream>
#include <algorithm>
#include "vector2.h"
#include "input.h"
#include "drawing.h"
#include "file.h"

enum WallPosition { WALL_FRONT, WALL_BACK };

struct Wall {
	Vector2 pointA = { -1, -1 };
	Vector2 pointB = { -1, -1 };

	int color[3] = { 255, 255, 255 };
};

struct WallNodeM {
	Wall splitter;

	std::vector<WallNodeM*> left;
	std::vector<WallNodeM*> right;
};

struct WallNode {
	Wall splitter;

	WallNode* left = nullptr;
	WallNode* right = nullptr;
};

class Joiner {
private:
	WallNode rootNode;
	std::vector<Wall> wallList;
	Wall tempWall;

	Vector2 colorPickerPosition = { 700 - 55, 700 - 55 };
	int colorPickerColor[3] = { 255, 255, 255 };

	Vector2 getProximity(Vector2 position);
	void importData();
	void exportData();
public:
	void initialize();
	void update();
	void draw();
};

extern Joiner joiner;