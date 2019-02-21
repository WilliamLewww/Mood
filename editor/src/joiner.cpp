#include "joiner.h"

std::vector<WallNodeM> convertWallToWallNodeM(std::vector<Wall> wallList) {
	std::vector<WallNodeM> tempList;
	for (Wall wall : wallList) { tempList.push_back({wall}); }

	return tempList;
}

Vector2 getLineIntersection(Vector2 pointA, Vector2 pointB, Vector2 pointC, Vector2 pointD) {
	Vector2 s1 = { pointB.x - pointA.x, pointB.y - pointA.y };
	Vector2 s2 = { pointC.x - pointD.x, pointC.y - pointD.y };

    float s, t;
    s = (-s1.y * (pointA.x - pointD.x) + s1.x * (pointA.y - pointD.y)) / (-s2.x * s1.y + s1.x * s2.y);
    t = ( s2.x * (pointA.y - pointD.y) - s2.y * (pointA.x - pointD.x)) / (-s2.x * s1.y + s1.x * s2.y);

    if (s >= 0 && s <= 1) { return { pointA.x + (t * s1.x), pointA.y + (t * s1.y) }; }

    return { -1, -1 };
}

std::vector<Wall> splitWall(Wall parentWall, Wall wall) {
	std::vector<Wall> splitList;

	Vector2 intersection = getLineIntersection(parentWall.pointA, parentWall.pointB, wall.pointA, wall.pointB);
	if (intersection.x != -1 && intersection.y != -1) {
		splitList.push_back({ wall.pointA, intersection, { wall.color[0], wall.color[1], wall.color[2] } });
		splitList.push_back({ wall.pointB, intersection, { wall.color[0], wall.color[1], wall.color[2] } });
	}

	return splitList;
}

WallNodeM generateBSPTreeList(std::vector<Wall> wallList) {
	WallNodeM nodeRoot;
	std::vector<WallNodeM> rNodeList = convertWallToWallNodeM(wallList);

	nodeRoot.splitter = rNodeList[0].splitter;
	rNodeList.erase(rNodeList.begin());

	std::vector<WallNodeM> additionalNodes;
	for (int x = 0; x < rNodeList.size(); x++) {
		std::vector<Wall> t = splitWall(nodeRoot.splitter, rNodeList[x].splitter);
		if (t.size() > 0) {
			additionalNodes.push_back({t[0]});
			additionalNodes.push_back({t[1]});
			rNodeList.erase(rNodeList.begin() + x);
			x -= 1;
		}
	}

	std::copy(additionalNodes.begin(), additionalNodes.end(), std::back_inserter(rNodeList));
	std::cout << rNodeList.size() << std::endl;

	return nodeRoot;
}

float getDistance(Vector2 pointA, Vector2 pointB) {
	return sqrt(pow(pointA.x - pointB.x, 2) + pow(pointA.y - pointB.y, 2));
}

void Joiner::initialize() { }

void Joiner::update() {
	if (input.checkLeftClickPress()) {
		Vector2 addPosition = { (float)input.getMouseX(), (float)input.getMouseY() };
		addPosition = getProximity(addPosition);
		if (tempWall.pointA.x != -1 && tempWall.pointB.x == -1) { tempWall.pointB = addPosition; }
		if (tempWall.pointA.x == -1 && tempWall.pointB.x == -1) { tempWall.pointA = addPosition; }

		if (tempWall.pointA.x != -1 && tempWall.pointB.x != -1) {
			tempWall.color[0] = colorPickerColor[0];
			tempWall.color[1] = colorPickerColor[1];
			tempWall.color[2] = colorPickerColor[2];

			wallList.push_back(tempWall);
			tempWall.pointA = { -1, -1 };
			tempWall.pointB = { -1, -1 };
		}
	}

	if (input.checkRightClickPress() && wallList.size() > 0) { wallList.erase(wallList.end()); }

	if (input.checkKeyDown(SDLK_i) && colorPickerColor[0] < 255) { colorPickerColor[0] += 1; }
	if (input.checkKeyDown(SDLK_j) && colorPickerColor[0] > 0) { colorPickerColor[0] -= 1; }
	if (input.checkKeyDown(SDLK_o) && colorPickerColor[1] < 255) { colorPickerColor[1] += 1; }
	if (input.checkKeyDown(SDLK_k) && colorPickerColor[1] > 0) { colorPickerColor[1] -= 1; }
	if (input.checkKeyDown(SDLK_p) && colorPickerColor[2] < 255) { colorPickerColor[2] += 1; }
	if (input.checkKeyDown(SDLK_l) && colorPickerColor[2] > 0) { colorPickerColor[2] -= 1; }

	if (input.checkGenerateBMPPress()) { generateBSPTreeList(wallList); }

	if (input.checkBackspacePress()) { importData(); }
	if (input.checkReturnPress()) { exportData(); }
}

void Joiner::draw() {
	for (int x = 0; x < wallList.size(); x++) {
		drawing.drawLine(wallList[x].pointA, wallList[x].pointB, wallList[x].color);
	}

	drawing.drawRect(colorPickerPosition, 50, 50, colorPickerColor);
}

Vector2 Joiner::getProximity(Vector2 position) {
	for (Wall wall : wallList) {
		if (getDistance(wall.pointA, position) < 25) { return wall.pointA; }
		if (getDistance(wall.pointB, position) < 25) { return wall.pointB; }
	}

	return position;
}

void Joiner::importData() {
	wallList.clear();
	std::vector<Vector2> positionList = file.getVerticesFromFile("map.data");
	std::vector<int> colorList = file.getColorsFromFile("color.data");

	for (int x = 0; x < positionList.size(); x += 2) {
		wallList.push_back({positionList[x], positionList[x + 1]});
	}

	for (int x = 0; x < wallList.size(); x++) {
		wallList[x].color[0] = colorList[(x * 3)];
		wallList[x].color[1] = colorList[(x * 3) + 1];
		wallList[x].color[2] = colorList[(x * 3) + 2];
	}
}

void Joiner::exportData() {
	std::ofstream map("map.data"), color("color.data");

	for (Wall wall : wallList) {
		map << wall.pointA.x << " " << wall.pointA.y << " " << wall.pointB.x << " " << wall.pointB.y << " ";
		color << wall.color[0] << " " << wall.color[1] << " " << wall.color[2] << " ";
	}

	map.close(); color.close();
}