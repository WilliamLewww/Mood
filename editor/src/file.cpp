#include "file.h"

File file;

std::vector<Vector2> File::getVerticesFromFile(const char* filename) {
	std::ifstream fin(filename);
	std::vector<Vector2> vertices;
	Vector2 temp_vertex = { -1, -1 };

	int x;
	while (fin >> x) {
		if (temp_vertex.y != -1) { vertices.push_back(temp_vertex); temp_vertex = { -1, -1 }; }
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