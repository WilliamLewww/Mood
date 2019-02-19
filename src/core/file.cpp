#include "file.h"

std::vector<Vector2> File::getVerticesFromFile(const char* filename) {
	std::ifstream fin(filename);
	std::vector<Vector2> vertices;
	Vector2 temp_vertex = Vector2(-1, -1);

	int x;
	while (fin >> x) {
		if (temp_vertex.y != -1) { vertices.push_back(temp_vertex); temp_vertex = Vector2(-1, -1); }
		if (temp_vertex.x == -1) { temp_vertex.x = x; }
		else { temp_vertex.y = x; }
	}

	vertices.push_back(temp_vertex);
	fin.close();

	return vertices;
}

std::vector<int> File::getColorsFromFile(const char* filename) {
	std::ifstream fin(filename);
	std::vector<int> color;

	int x;
	while (fin >> x) { color.push_back(x); }

	fin.close();

	return color;
}

std::map<std::string, int> File::getConfigurationFromFile(const char* filename) {
	std::map<std::string, int> configurations;

	std::ifstream configFile(filename);
	std::string lineFromFile;
	while (std::getline(configFile, lineFromFile)) {
		if (lineFromFile[0] != '#' && lineFromFile[0] != '@') {
			configurations[lineFromFile.substr(0, lineFromFile.find(" "))] 
				= atoi(lineFromFile.substr(lineFromFile.find(" ") + 1, lineFromFile.length()).c_str());
		}
	}

	configFile.close();

	return configurations;
}

std::map<std::string, std::string> File::getNameConfigurationFromFile(const char* filename) {
	std::map<std::string, std::string> configurations;

	std::ifstream configFile(filename);
	std::string lineFromFile;
	while (std::getline(configFile, lineFromFile)) {
		if (lineFromFile[0] == '@') {
			configurations[lineFromFile.substr(1, lineFromFile.find(" ") - 1)] 
				= lineFromFile.substr(lineFromFile.find(" ") + 1, lineFromFile.length()).c_str();
		}
	}

	configFile.close();

	return configurations;
}

File file;