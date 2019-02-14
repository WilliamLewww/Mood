#include "first_person.h"

void FirstPerson::drawWall(Wall wall) {
	getDistanceProjection(wall.pointA);
}

float FirstPerson::getDistanceProjection(Vector2 position) {
	float s = sin(drawing.degreeToRadians(*cameraAngle));
	float c = cos(drawing.degreeToRadians(*cameraAngle));

	Vector2 tempPosition = position - *cameraPosition;
	return ((tempPosition.x * c) - (tempPosition.y * s));
}

FirstPerson::FirstPerson() {
	cameraPosition = nullptr;
	cameraAngle = nullptr;
}

FirstPerson::FirstPerson(Vector2* cameraPosition, float* cameraAngle) {
	this->cameraPosition = cameraPosition;
	this->cameraAngle = cameraAngle;
}

void FirstPerson::draw(Wall* wallArray, int wallCount) {
	drawing.drawRectOutline(Vector2(0, 0), configuration.getScreenWidth(), configuration.getScreenHeight());

	glPushMatrix();
	glTranslatef((configuration.getScreenWidth() / 2.0) - cameraPosition->x, (configuration.getScreenHeight() / 2.0) - cameraPosition->y, 0);

	glTranslatef(cameraPosition->x - (configuration.getScreenWidth() / 2.0), cameraPosition->y - (configuration.getScreenHeight() / 2.0), 0);
	glRotatef(*cameraAngle - 90, 0, 0, 1);
	glTranslatef(-(cameraPosition->x - (configuration.getScreenWidth() / 2.0)), -(cameraPosition->y - (configuration.getScreenHeight() / 2.0)), 0);

	for (int x = 0; x < wallCount; x++) {
		drawWall(wallArray[x]);
	}
	glPopMatrix();
}