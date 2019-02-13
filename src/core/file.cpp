#include "file.h"

void File::exportSplits(int seed, std::vector<float> splits, float finalTime) {
	std::ofstream out(std::to_string(seed) + ".splits");

	out << "Final Time: " << finalTime << "\n\n";
	out << "Splits:\n";
	for (int x = 0; x < splits.size(); x++) {
		if (x == splits.size() - 1) { out << splits[x]; }
		else { out << splits[x] << "\n"; }
	}

	out.close();
}

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

std::vector<std::vector<Vector2>> File::getVerticesFromFileFull(const char* filename) {
	std::vector<std::vector<Vector2>> fullList;
	std::vector<Vector2> vertexList;

	Vector2 temp_vertex;

	std::ifstream configFile(filename);
	std::string lineFromFile;

	std::string tempInt = "";

	while (std::getline(configFile, lineFromFile)) {
		temp_vertex = Vector2(-1, -1);

		for (char ch : lineFromFile) {
			if (ch != ' ') {
				tempInt += ch;
			}
			else {
				if (temp_vertex.y != -1) { vertexList.push_back(temp_vertex); temp_vertex = Vector2(-1, -1); }
				if (temp_vertex.x == -1) { temp_vertex.x = std::stoi(tempInt); }
				else { temp_vertex.y = std::stoi(tempInt); }

				tempInt = "";
			}
		}

		if (temp_vertex.x != -1 && temp_vertex.y != -1) {
			vertexList.push_back(temp_vertex);
		}

		fullList.push_back(vertexList);
		vertexList.clear();
	}

	configFile.close();
	return fullList;
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