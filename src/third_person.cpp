#include "third_person.h"

ThirdPerson::ThirdPerson() {
	cameraPosition = nullptr;
	cameraAngle = nullptr;
}

ThirdPerson::ThirdPerson(Vector2* cameraPosition, float* cameraAngle) {
	this->cameraPosition = cameraPosition;
	this->cameraAngle = cameraAngle;
}

void ThirdPerson::draw(Wall* wallArray, int wallCount) {
	drawing.drawRectOutline(Vector2(0, 0), configuration.getScreenWidth(), configuration.getScreenHeight());
	glPushMatrix();
	for (int x = 0; x < wallCount; x++) {
		drawing.drawLine(wallArray[x].pointA, wallArray[x].pointB, wallArray[x].color);
	}
	drawing.drawTriangle(*cameraPosition - Vector2(10.0 / 2.0, 10.0 / 2.0), 10, 10, *cameraAngle);
	glPopMatrix();
}