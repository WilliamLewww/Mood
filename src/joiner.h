#pragma once
#include "core/configuration.h"
#include "core/drawing.h"
#include "core/input.h"
#include "core/file.h"
#include "third_person.h"
#include "third_person_translated.h"
#include "first_person.h"
#include "wall.h"

class Joiner {
private:
	ThirdPerson thirdPerson;
	ThirdPersonTranslated thirdPersonTranslated;
	FirstPerson firstPerson;

	Wall* wallArray;
	int wallCount;

	Vector2 cameraPosition;
	float cameraAngle;
public:
	int seed;
	
	void initialize();
	void update();
	void draw();
};

extern Joiner joiner;