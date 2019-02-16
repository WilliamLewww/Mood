#include "joiner.h"

Joiner joiner;

void Joiner::initialize() {
	std::vector<Vector2> positionList = file.getVerticesFromFile("map.data");

	wallCount = positionList.size() / 2;
	wallArray = new Wall[wallCount];
	for (int x = 0; x < positionList.size(); x += 2) {
		wallArray[x / 2] = { positionList[x], positionList[x + 1] };
	}

	cameraPosition = Vector2(50, 50);
	cameraAngle = 0;

	thirdPerson = ThirdPerson(&cameraPosition, &cameraAngle);
	thirdPersonTranslated = ThirdPersonTranslated(&cameraPosition, &cameraAngle);
	firstPerson = FirstPerson(&cameraPosition, &cameraAngle);
}

void Joiner::update() {
	if (input.checkKeyDown(SDLK_LEFT)) { cameraAngle += 1; }
	if (input.checkKeyDown(SDLK_RIGHT)) { cameraAngle -= 1; }

	if (input.checkKeyDown(SDLK_UP)) { cameraPosition += Vector2(1.5 * cos(drawing.degreeToRadians(-cameraAngle)), 1.5 * sin(drawing.degreeToRadians(-cameraAngle))); }
	if (input.checkKeyDown(SDLK_DOWN)) { cameraPosition -= Vector2(1.5 * cos(drawing.degreeToRadians(-cameraAngle)), 1.5 * sin(drawing.degreeToRadians(-cameraAngle))); }

	firstPerson.update();
}

void Joiner::draw() {
	glPushMatrix();
	glViewport(0, configuration.getScreenHeight() / 2, configuration.getScreenWidth() / 2, configuration.getScreenHeight() / 2);
	thirdPerson.draw(wallArray, wallCount);
	glViewport(0, 0, configuration.getScreenWidth() / 2, configuration.getScreenHeight() / 2);
	thirdPersonTranslated.draw(wallArray, wallCount);
	glViewport(configuration.getScreenWidth() / 2, 0, configuration.getScreenWidth() / 2, configuration.getScreenHeight() / 2);
	firstPerson.draw(wallArray, wallCount);
	glPopMatrix();
}