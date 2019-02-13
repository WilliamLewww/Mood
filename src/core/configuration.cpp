#include "configuration.h"

Configuration configuration;

void Configuration::initialize() {
	grabConfiguration();
	linkScreenSize();
}

void Configuration::grabConfiguration() {
	configurations = file.getConfigurationFromFile("config.txt");
	nameConfigurations = file.getNameConfigurationFromFile("config.txt");
}

void Configuration::linkScreenSize() {
	screenWidth = getConfigurations()["ScreenWidth"];
	screenHeight = getConfigurations()["ScreenHeight"];
}