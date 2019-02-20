#include <vector>
#include <cmath>
#include <SDL2\SDL_syswm.h>
#include <SDL2\SDL.h>
#include <SDL2\SDL_opengl.h>
#include <SDL2\SDL_ttf.h>

struct Vector2 {
	int x;
	int y;
};

struct Wall {
	Vector2 pointA = { -1, -1 };
	Vector2 pointB = { -1, -1 };

	int color[3] = { 255, 255, 255 };
};

std::vector<Wall> wallList;
Wall tempWall;

SDL_Event event;
SDL_Window* displayWindow;
SDL_GLContext displayContext;

bool isRunning = true;

int mouseX, mouseY;
bool leftClickPress = false;

void update();
void render();
void drawLine(Vector2 a, Vector2 b, int color[3]);
Vector2 getProximity(Vector2 position);

int main(int argc, char *argv[]) {
	displayWindow = SDL_CreateWindow("Mood Editor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 700, 700, SDL_WINDOW_OPENGL);
	displayContext = SDL_GL_CreateContext(displayWindow);
	glOrtho(-350, 350, 350, -350, 0, 1);
	
	TTF_Init();
	glEnable(GL_BLEND); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	while (isRunning) {
		leftClickPress = false;

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) { isRunning = false; }
			if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) { leftClickPress = true; }
			if (event.type == SDL_MOUSEMOTION) {
				mouseX = event.motion.x;
				mouseY = event.motion.y;
			}
		}

		update();
		render();
	}

	SDL_Quit();

	return 0;
}

void update() {
	if (leftClickPress) {
		Vector2 addPosition = { mouseX, mouseY };
		addPosition = getProximity(addPosition);
		if (tempWall.pointA.x != -1 && tempWall.pointB.x == -1) {
			tempWall.pointB = addPosition;
		}

		if (tempWall.pointA.x == -1 && tempWall.pointB.x == -1) {
			tempWall.pointA = addPosition;
		}

		if (tempWall.pointA.x != -1 && tempWall.pointB.x != -1) {
			wallList.push_back(tempWall);
			tempWall.pointA = { -1, -1 };
			tempWall.pointB = { -1, -1 };
		}
	}
}

void render() {
	SDL_GL_MakeCurrent(displayWindow, displayContext);
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	for (int x = 0; x < wallList.size(); x++) {
		drawLine(wallList[x].pointA, wallList[x].pointB, wallList[x].color);
	}
	glPopMatrix();

	SDL_GL_SwapWindow(displayWindow);
}

double convertColorFloatToRGB(int rgbValue) {
	return (double)rgbValue / 255;
}

void drawLine(Vector2 a, Vector2 b, int color[3]) {
	glBegin(GL_LINES);
	glColor4f(convertColorFloatToRGB(color[0]), convertColorFloatToRGB(color[1]), convertColorFloatToRGB(color[2]), 1);
	glVertex2f(a.x - 350.0, a.y - 350.0);
	glVertex2f(b.x - 350.0, b.y - 350.0);
	glEnd();
}

float getDistance(Vector2 pointA, Vector2 pointB) {
	return sqrt(pow(pointA.x - pointB.x, 2) + pow(pointA.y - pointB.y, 2));
}

Vector2 getProximity(Vector2 position) {
	for (Wall wall : wallList) {
		if (getDistance(wall.pointA, position) < 25) { return wall.pointA; }
		if (getDistance(wall.pointB, position) < 25) { return wall.pointB; }
	}

	return position;
}