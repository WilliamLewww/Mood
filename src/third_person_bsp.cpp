#include "third_person_bsp.h"

ThirdPersonBSP::ThirdPersonBSP() {
	cameraPosition = nullptr;
	cameraAngle = nullptr;
}

ThirdPersonBSP::ThirdPersonBSP(Vector2* cameraPosition, float* cameraAngle) {
	this->cameraPosition = cameraPosition;
	this->cameraAngle = cameraAngle;
}

void ThirdPersonBSP::draw(WallNode *rootNode) {
	drawing.drawRectOutline(Vector2(0, 0), configuration.getScreenWidth(), configuration.getScreenHeight());
	glPushMatrix();
	iterateBSPTree(rootNode, 125);
	drawing.drawTriangle(*cameraPosition - Vector2(10.0 / 2.0, 10.0 / 2.0), 10, 10, *cameraAngle);
	glPopMatrix();
}

void ThirdPersonBSP::drawWall(Wall wall, int colorA) {
	drawing.drawLine(wall.pointA, wall.pointB, wall.color, colorA);
}

void ThirdPersonBSP::iterateBSPTree(WallNode *node, int colorA) {
    if(node == nullptr) { return; }
    if (getWallPosition(node->splitter, *cameraPosition) == WALL_FRONT) { 
    	iterateBSPTree(node->left, colorA - 50);
    	drawWall(node->splitter, colorA);
    	iterateBSPTree(node->right, colorA + 50); 
    }
    else { 
    	iterateBSPTree(node->right, colorA - 50);
    	drawWall(node->splitter, colorA);
    	iterateBSPTree(node->left, colorA + 50);
    }
}