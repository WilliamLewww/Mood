#pragma once
#include <vector>
#include <map>
#include <fstream>
#include "vector2.h"

class File {
public:
	std::vector<int> getColorsFromFile(const char* filename);
	std::vector<Vector2> getVerticesFromFile(const char* filename);
	std::map<std::string, int> getConfigurationFromFile(const char* filename);
	std::map<std::string, std::string> getNameConfigurationFromFile(const char* filename);
};

extern File file;