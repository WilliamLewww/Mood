#include "joiner.h"

std::ostream &operator<<(std::ostream &os, Wall const &wall) {
	return os << "(" << wall.pointA << "|" << wall.pointB << ")" << ":" << wall.color[0] << "," << wall.color[1] << "," << wall.color[2];
}

bool operator==(Wall a, Wall b) {
	return (a.pointA.x == b.pointA.x && a.pointA.y == b.pointA.y &&
			a.pointB.x == b.pointB.x && a.pointB.y == b.pointB.y);
}

bool operator!=(Wall a, Wall b) {
	return (a.pointA.x != b.pointA.x || a.pointA.y != b.pointA.y ||
			a.pointB.x != b.pointB.x || a.pointB.y != b.pointB.y);
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

WallPosition getWallPosition(Wall parentWall, Wall wall) {
	float slope = (parentWall.pointB.y - parentWall.pointA.y) /  (parentWall.pointB.x - parentWall.pointA.x);
	float yInt = parentWall.pointA.y + (-slope * parentWall.pointA.x);
	
	if (wall.pointA.y > (slope * wall.pointA.x) + yInt) {
		return WALL_FRONT;
	}

	return WALL_BACK;
}

void splitAndPlaceWalls(std::vector<WallNodeM*> newWallList, WallNodeM *rootNode) {
	// split all walls and place it into the new master list
	std::vector<WallNodeM*> additionalWalls;
	for (int x = 0; x < newWallList.size(); x++) {
		if (rootNode->splitter != newWallList[x]->splitter) {
			std::vector<Wall> t = splitWall(rootNode->splitter, newWallList[x]->splitter);
			if (t.size() > 0) {
				additionalWalls.push_back(new WallNodeM{t[0]});
				additionalWalls.push_back(new WallNodeM{t[1]});
				newWallList.erase(newWallList.begin() + x);
				x -= 1;
			}
		}
	}
	std::copy(additionalWalls.begin(), additionalWalls.end(), std::back_inserter(newWallList));

	// place walls into front(right) or back(left) list
	for (WallNodeM *wallNode : newWallList) {
		if (rootNode->splitter != wallNode->splitter) {
			if (getWallPosition(rootNode->splitter, wallNode->splitter) == WALL_FRONT) { rootNode->right.push_back(new WallNodeM{wallNode->splitter}); }
			else { rootNode->left.push_back(new WallNodeM{wallNode->splitter}); }
		}
	}
	newWallList.clear();
}

WallNode* propagateTreePreOrderR(WallNodeM *nodeM) {
	WallNode *tempNode = new WallNode{nodeM->splitter};
	if (nodeM->right.size() > 1) {
		std::vector<WallNodeM*> newWallList = nodeM->right;
		WallNodeM* rootNode = {nodeM->right[0]};

		splitAndPlaceWalls(newWallList, rootNode);
		nodeM->right.clear();
		nodeM->right.push_back(rootNode);
	}

    if (nodeM->left.size() > 1) {
    	std::vector<WallNodeM*> newWallList = nodeM->left;
		WallNodeM* rootNode = {nodeM->left[0]};

		splitAndPlaceWalls(newWallList, rootNode);
		nodeM->left.clear();
		nodeM->left.push_back(rootNode);
    }

    if (nodeM->right.size() > 0) { tempNode->right = propagateTreePreOrderR(nodeM->right[0]); }
    if (nodeM->left.size() > 0) { tempNode->left = propagateTreePreOrderR(nodeM->left[0]); }

    return tempNode;
}

WallNode* generateBSPTreeList(std::vector<Wall> wallList) {
	std::vector<WallNodeM*> newWallList;
	for (Wall wall : wallList) { newWallList.push_back(new WallNodeM{wall}); }
	WallNodeM* rootNode = {newWallList[0]};
	splitAndPlaceWalls(newWallList, rootNode);

	return propagateTreePreOrderR(rootNode);
}

float getDistance(Vector2 pointA, Vector2 pointB) {
	return sqrt(pow(pointA.x - pointB.x, 2) + pow(pointA.y - pointB.y, 2));
}

void Joiner::initialize() { }

// Thanks Valiano (https://stackoverflow.com/a/50650932/3269446)
void printTree(WallNode* root, const std::string& prefix) {
    if (root == NULL) { return; }

    bool hasLeft = (root->left != NULL);
    bool hasRight = (root->right != NULL);

    if (!hasLeft && !hasRight) { return; }

    std::cout << prefix;
    std::cout << ((hasLeft  && hasRight) ? "----" : "");
    std::cout << ((!hasLeft && hasRight) ? "----" : "");

    if (hasRight) {
        bool printStrand = (hasLeft && hasRight && (root->right->right != NULL || root->right->left != NULL));
        std::string newPrefix = prefix + (printStrand ? "|   " : "    ");
        std::cout << "F: " << root->right->splitter << std::endl;
        printTree(root->right, newPrefix);
    }

    if (hasLeft) {
        std::cout << (hasRight ? prefix : "") << "----" << "B: " << root->left->splitter << std::endl;
        printTree(root->left, prefix + "    ");
    }
}

void writeTreeFile(WallNode *node, std::ostream &os) {
	if (node == nullptr) { os << "# "; } 
	else {
		os << node->splitter << " ";
		writeTreeFile(node->left, os);
		writeTreeFile(node->right, os);
	}
}

WallNode* readBinaryTree(WallNode *node, std::ifstream &fin) {
	std::string token;
	fin >> token;

	if (token == "#") { return nullptr; }
	else {
		token.erase(std::remove(token.begin(), token.end(), '('), token.end());
		token.erase(std::remove(token.begin(), token.end(), ')'), token.end());

		std::string pointAS = token.substr(0, token.find('|'));
		std::string pointBS = token.substr(token.find('|') + 1);

		Vector2 pointA = { std::stof(pointAS.substr(0, pointAS.find(','))), std::stof(pointAS.substr(pointAS.find(',') + 1)) };
		Vector2 pointB = { std::stof(pointBS.substr(0, pointBS.find(','))), std::stof(pointBS.substr(pointBS.find(',') + 1)) };

		token = token.substr(token.find(':') + 1);
		int colorR = std::stoi(token.substr(0, token.find(',')));
		token = token.substr(token.find(',') + 1);
		int colorG = std::stoi(token.substr(0, token.find(',')));
		token = token.substr(token.find(',') + 1);
		int colorB = std::stoi(token);

		node = new WallNode{{pointA, pointB, {colorR, colorG, colorB}}};
		node->left = readBinaryTree(node->left, fin);
	 	node->right = readBinaryTree(node->right, fin);
	}

	return node;
}

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

	std::ifstream tree("bsp_tree.data");
	rootNode = *readBinaryTree(&rootNode, tree);

	std::cout << rootNode.splitter << std::endl;
    printTree(&rootNode, "");
    std::cout << std::endl;
}

void Joiner::exportData() {
	std::ofstream map("map.data"), color("color.data");

	for (Wall wall : wallList) {
		map << wall.pointA.x << " " << wall.pointA.y << " " << wall.pointB.x << " " << wall.pointB.y << " ";
		color << wall.color[0] << " " << wall.color[1] << " " << wall.color[2] << " ";
	}

	map.close(); color.close();

	rootNode = *generateBSPTreeList(wallList); 

    std::cout << rootNode.splitter << std::endl;
    printTree(&rootNode, "");
    std::cout << std::endl;

    std::ofstream tree("bsp_tree.data");
    writeTreeFile(&rootNode, tree);
}