#pragma once
#include "core/configuration.h"
#include "core/drawing.h"
#include "core/input.h"
#include "core/file.h"
#include "core/timer.h"
#include "third_person.h"
#include "third_person_translated.h"
#include "third_person_bsp.h"
#include "first_person.h"
#include "wall.h"

class Joiner {
private:
	ThirdPerson thirdPerson;
	ThirdPersonTranslated thirdPersonTranslated;
	ThirdPersonBSP thirdPersonBSP;
	FirstPerson firstPerson;

	WallNode rootNode;
	Wall* wallArray;
	int wallCount;

	Vector2 cameraPosition;
	float cameraAngle;

	float speed = 100;
public:
	int seed;
	
	void initialize();
	void update();
	void draw();
};