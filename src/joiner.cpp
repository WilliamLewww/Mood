#include "joiner.h"

Joiner joiner;

void Joiner::initialize() {
	std::vector<Vector2> positionList = file.getVerticesFromFile("map.data");
	std::vector<int> colorList = file.getColorsFromFile("color.data");

	wallCount = positionList.size() / 2;
	wallArray = new Wall[wallCount];
	for (int x = 0; x < positionList.size(); x += 2) {
		wallArray[x / 2] = { positionList[x], positionList[x + 1] };
	}

	for (int x = 0; x < wallCount; x++) {
		wallArray[x].color[0] = colorList[(x * 3)];
		wallArray[x].color[1] = colorList[(x * 3) + 1];
		wallArray[x].color[2] = colorList[(x * 3) + 2];
	}

	cameraPosition = Vector2(50, 50);
	cameraAngle = 0;

	thirdPerson = ThirdPerson(&cameraPosition, &cameraAngle);
	thirdPersonTranslated = ThirdPersonTranslated(&cameraPosition, &cameraAngle);
	firstPerson = FirstPerson(&cameraPosition, &cameraAngle);
}

void Joiner::update() {
	if (input.checkKeyDown(SDLK_LEFT)) { cameraAngle += speed * timer.getTimeSeconds(); }
	if (input.checkKeyDown(SDLK_RIGHT)) { cameraAngle -= speed * timer.getTimeSeconds(); }

	if (input.checkKeyDown(SDLK_UP)) { cameraPosition += Vector2(cos(drawing.degreeToRadians(-cameraAngle)), sin(drawing.degreeToRadians(-cameraAngle))) * speed * timer.getTimeSeconds(); }
	if (input.checkKeyDown(SDLK_DOWN)) { cameraPosition -= Vector2(cos(drawing.degreeToRadians(-cameraAngle)), sin(drawing.degreeToRadians(-cameraAngle))) * speed * timer.getTimeSeconds(); }

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