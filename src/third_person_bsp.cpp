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
	drawing.drawTriangle(Vector2((configuration.getScreenWidth() / 2.0) - (10.0 / 2), (configuration.getScreenHeight() / 2.0) - (10.0 / 2)), 10, 10, 90);

	glPushMatrix();
	glTranslatef((configuration.getScreenWidth() / 2.0), (configuration.getScreenHeight() / 2.0), 0);
	iterateBSPTree(rootNode, 125);
	glPopMatrix();
}

void ThirdPersonBSP::drawWall(Wall wall, int colorA) {
	//Transform the vertexes relative to the player
	float tx1 = wall.pointA.x - cameraPosition->x, ty1 = wall.pointA.y - cameraPosition->y;
	float tx2 = wall.pointB.x - cameraPosition->x, ty2 = wall.pointB.y - cameraPosition->y;

	//Rotate the vertexes around the player's view
	float s = sin(drawing.degreeToRadians(-*cameraAngle + 180));
	float c = cos(drawing.degreeToRadians(-*cameraAngle + 180));

	float tz1 = (tx1 * c) + (ty1 * s);
	float tz2 = (tx2 * c) + (ty2 * s);
	tx1 = (tx1 * s) - (ty1 * c);
	tx2 = (tx2 * s) - (ty2 * c);

	drawing.drawLine(Vector2(tx1, tz1), Vector2(tx2, tz2), wall.color, colorA);
}

void ThirdPersonBSP::iterateBSPTree(WallNode *node, int colorA) {
    if(node == nullptr) { return; }
    if (getWallPosition(node->splitter, *cameraPosition) == WALL_FRONT) { 
    	iterateBSPTree(node->left, colorA - 75);
    	drawWall(node->splitter, colorA);
    	iterateBSPTree(node->right, colorA + 75); 
    }
    else { 
    	iterateBSPTree(node->right, colorA - 75);
    	drawWall(node->splitter, colorA);
    	iterateBSPTree(node->left, colorA + 75);
    }
}