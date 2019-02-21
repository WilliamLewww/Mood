#include <SDL2\SDL_syswm.h>
#include <SDL2\SDL.h>
#include <SDL2\SDL_opengl.h>
#include <SDL2\SDL_ttf.h>
#include "src\joiner.h"
#include "src\drawing.h"

Joiner joiner;

SDL_Event event;
SDL_Window* displayWindow;
SDL_GLContext displayContext;

bool isRunning = true;

void update();
void render();

int main(int argc, char *argv[]) {
	displayWindow = SDL_CreateWindow("Mood Editor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 700, 700, SDL_WINDOW_OPENGL);
	displayContext = SDL_GL_CreateContext(displayWindow);
	glOrtho(-350, 350, 350, -350, 0, 1);
	
	TTF_Init();
	glEnable(GL_BLEND); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	joiner.initialize();

	while (isRunning) {
		input.refreshInput();

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) { isRunning = false; }
			input.getTrigger(event);
		}

		update();
		render();
	}

	SDL_Quit();

	return 0;
}

void update() {
	joiner.update();
}

void render() {
	SDL_GL_MakeCurrent(displayWindow, displayContext);
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	joiner.draw();
	glPopMatrix();

	SDL_GL_SwapWindow(displayWindow);
}