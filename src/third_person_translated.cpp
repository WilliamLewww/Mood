#include "third_person_translated.h"

ThirdPersonTranslated::ThirdPersonTranslated() {
	cameraPosition = nullptr;
	cameraAngle = nullptr;
}

ThirdPersonTranslated::ThirdPersonTranslated(Vector2* cameraPosition, float* cameraAngle) {
	this->cameraPosition = cameraPosition;
	this->cameraAngle = cameraAngle;
}

void ThirdPersonTranslated::draw(Wall* wallArray, int wallCount) {
	drawing.drawRectOutline(Vector2(0, 0), configuration.getScreenWidth(), configuration.getScreenHeight());
	drawing.drawTriangle(Vector2((configuration.getScreenWidth() / 2.0) - (10.0 / 2), (configuration.getScreenHeight() / 2.0) - (10.0 / 2)), 10, 10, 90);
	glPushMatrix();
	glTranslatef((configuration.getScreenWidth() / 2.0), (configuration.getScreenHeight() / 2.0), 0);	
	for (int x = 0; x < wallCount; x++) {
		drawWall(wallArray[x]);	
	}
	glPopMatrix();
}

void ThirdPersonTranslated::drawWall(Wall wall) {
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

	drawing.drawLine(Vector2(tx1, tz1), Vector2(tx2, tz2), wall.color);
}