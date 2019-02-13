#pragma once
#include <vector>
#include <map>
#include <fstream>
#include "vector2.h"

class File {
public:
	void exportSplits(int index, std::vector<float> splits, float finalTime);

	std::vector<std::vector<Vector2>> getVerticesFromFileFull(const char* filename);
	std::vector<Vector2> getVerticesFromFile(const char* filename);
	std::map<std::string, int> getConfigurationFromFile(const char* filename);
	std::map<std::string, std::string> getNameConfigurationFromFile(const char* filename);
};

extern File file;