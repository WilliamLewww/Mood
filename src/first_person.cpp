#include "first_person.h"

int color[3] = { 255, 0, 0 };

float crossMultiply(float x1, float y1, float x2, float y2) {
	return (x1*y2) - (y1*x2);
}

Vector2 getIntersection(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
	Vector2 position = Vector2(0, 0);

	position.x = crossMultiply(x1, y1, x2, y2);
	position.y = crossMultiply(x3, y3, x4, y4);
	float det  = crossMultiply(x1-x2, y1-y2, x3-x4, y3-y4);
  	position.x = crossMultiply(position.x, x1-x2, position.y, x3-x4) / det;
  	position.y = crossMultiply(position.x, y1-y2, position.y, y3-y4) / det;

	return position;
}

FirstPerson::FirstPerson() {
	cameraPosition = nullptr;
	cameraAngle = nullptr;
}

FirstPerson::FirstPerson(Vector2* cameraPosition, float* cameraAngle) {
	this->cameraPosition = cameraPosition;
	this->cameraAngle = cameraAngle;
}

void FirstPerson::update() {

}

void FirstPerson::draw(Wall* wallArray, int wallCount) {
	drawing.drawRectOutline(Vector2(0, 0), configuration.getScreenWidth(), configuration.getScreenHeight());

	glPushMatrix();
	glTranslatef((configuration.getScreenWidth() / 2.0), (configuration.getScreenHeight() / 2.0), 0);
	for (int x = 0; x < wallCount; x++) {
		drawWall(wallArray[x]);
	}
	glPopMatrix();
}

void FirstPerson::drawWall(Wall wall) {
	//Transform the vertexes relative to the player
	float tx1 = wall.pointA.x - cameraPosition->x, ty1 = wall.pointA.y - cameraPosition->y;
	float tx2 = wall.pointB.x - cameraPosition->x, ty2 = wall.pointB.y - cameraPosition->y;

	//Rotate the vertexes around the player's view
	float s = sin(drawing.degreeToRadians(-*cameraAngle));
	float c = cos(drawing.degreeToRadians(-*cameraAngle));

	float tz1 = (tx1 * c) + (ty1 * s);
	float tz2 = (tx2 * c) + (ty2 * s);
	tx1 = (tx1 * s) - (ty1 * c);
	tx2 = (tx2 * s) - (ty2 * c);

	if (tz1 > 0 || tz2 > 0) {
		Vector2 i1 = getIntersection(tx1, tz1, tx2, tz2, -0.0001, 0.0001, -280.0, 5.0);
		Vector2 i2 = getIntersection(tx1, tz1, tx2, tz2,  0.0001, 0.0001,  280.0, 5.0);

		if (tz1 <= 0) {
			if (i1.y > 0) {
				tx1 = i1.x;
				tz1 = i1.y;
			}
			else {
				tx1 = i2.x;
				tz1 = i2.y;
			}
		}

		if (tz2 <= 0) {
			if (i1.y > 0) {
				tx2 = i1.x;
				tz2 = i1.y;
			}
			else {
				tx2 = i2.x;
				tz2 = i2.y;
			}
		}

		float x1 = -tx1 * 120.0 / tz1, y1a = -(120.0 * 25.0) / tz1, y1b = (120.0 * 25.0) / tz1;
		float x2 = -tx2 * 120.0 / tz2, y2a = -(120.0 * 25.0) / tz2, y2b = (120.0 * 25.0) / tz2;

		std::vector<Vector2> polygonA = { Vector2(x1, y1a), Vector2(x2, y2a), Vector2(x2, y2b), Vector2(x1, y1b) };
		drawing.drawPolygon(polygonA, wall.color);
	}
}

void FirstPerson::drawUsingBSP(WallNode *rootNode) {
	drawing.drawRectOutline(Vector2(0, 0), configuration.getScreenWidth(), configuration.getScreenHeight());

	glPushMatrix();
	glTranslatef((configuration.getScreenWidth() / 2.0), (configuration.getScreenHeight() / 2.0), 0);
	iterateBSPTree(rootNode);
	glPopMatrix();
}

//right(front) left(back)
void FirstPerson::iterateBSPTree(WallNode *node) {
    if(node == nullptr) { return; }
    if (getWallPosition(node->splitter, *cameraPosition) == WALL_FRONT) { 
    	iterateBSPTree(node->left);
    	drawWall(node->splitter);
    	iterateBSPTree(node->right); 
    }
    else { 
    	iterateBSPTree(node->right);
    	drawWall(node->splitter);
    	iterateBSPTree(node->left);
    }
}