#pragma once
#include <iostream>

struct Vector2 {
	float x;
	float y;
};

std::ostream &operator<<(std::ostream &os, Vector2 const &m);