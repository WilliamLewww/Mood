#include "engine.h"

Engine engine;

int main(int argc, char *argv[]) {
	engine.initialize();
	engine.start();
	engine.quit();

	return 0;
}