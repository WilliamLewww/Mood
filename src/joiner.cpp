#include "joiner.h"

Joiner joiner;

void Joiner::initialize() {
	wallCount = 1;
	wallArray = new Wall[wallCount];
	wallArray[0] = { Vector2(50, 50), Vector2(250, 250), 15 };

	cameraPosition = Vector2(100, 200);
	cameraAngle = 0;

	thirdPerson = ThirdPerson(&cameraPosition, &cameraAngle);
	thirdPersonTranslated = ThirdPersonTranslated(&cameraPosition, &cameraAngle);
}

void Joiner::update() {
	if (input.checkKeyDown(SDLK_LEFT)) { cameraAngle += 1; }
	if (input.checkKeyDown(SDLK_RIGHT)) { cameraAngle -= 1; }

	if (input.checkKeyDown(SDLK_UP)) {
		cameraPosition += Vector2(1.5 * cos(drawing.degreeToRadians(-cameraAngle)), 1.5 * sin(drawing.degreeToRadians(-cameraAngle)));
	}

	if (input.checkKeyDown(SDLK_DOWN)) {
		cameraPosition -= Vector2(1.5 * cos(drawing.degreeToRadians(-cameraAngle)), 1.5 * sin(drawing.degreeToRadians(-cameraAngle)));
	}
}

void Joiner::draw() {
	glPushMatrix();
	glViewport(0, configuration.getScreenHeight() / 2, configuration.getScreenWidth() / 2, configuration.getScreenHeight() / 2);
	thirdPerson.draw(wallArray, wallCount);
	glViewport(0, 0, configuration.getScreenWidth() / 2, configuration.getScreenHeight() / 2);
	thirdPersonTranslated.draw(wallArray, wallCount);
	glPopMatrix();
}