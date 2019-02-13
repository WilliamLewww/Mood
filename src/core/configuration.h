#pragma once
#include "file.h"

class Configuration {
private:
	int screenWidth, screenHeight;
	std::map<std::string, int> configurations;
	std::map<std::string, std::string> nameConfigurations;

	void grabConfiguration();
	void linkScreenSize();
public:
	inline std::map<std::string, int> getConfigurations() { return configurations; };
	inline std::map<std::string, std::string> getNameConfigurations() { return nameConfigurations; };
	inline void setConfiguration(std::string name, int value) { configurations[name] = value; };

	inline int getScreenWidth() { return screenWidth; };
	inline int getScreenHeight() { return screenHeight; };

	void initialize();
};

extern Configuration configuration;