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
	drawing.drawTriangle(Vector2((configuration.getScreenWidth() / 2.0) - (25.0 / 2), (configuration.getScreenHeight() / 2.0) - (25.0 / 2)), 25, 25, 90);
	glPushMatrix();
	glTranslatef((configuration.getScreenWidth() / 2.0) - cameraPosition->x, (configuration.getScreenHeight() / 2.0) - cameraPosition->y, 0);

	glTranslatef(cameraPosition->x - (configuration.getScreenWidth() / 2.0), cameraPosition->y - (configuration.getScreenHeight() / 2.0), 0);
	glRotatef(*cameraAngle - 90, 0, 0, 1);
	glTranslatef(-(cameraPosition->x - (configuration.getScreenWidth() / 2.0)), -(cameraPosition->y - (configuration.getScreenHeight() / 2.0)), 0);

	for (int x = 0; x < wallCount; x++) {
		drawing.drawLine(wallArray[x].pointA, wallArray[x].pointB);
	
	}
	glPopMatrix();
}