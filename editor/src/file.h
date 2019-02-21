#pragma once
#include <vector>
#include <fstream>
#include "vector2.h"

class File {
public:
	std::vector<Vector2> getVerticesFromFile(const char* filename);
	std::vector<int> getColorsFromFile(const char* filename);
};

extern File file;