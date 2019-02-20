#include <vector>
#include <cmath>
#include <algorithm>
#include <fstream>
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

Vector2 colorPickerPosition = { 700 - 55, 700 - 55 };
int colorPickerColor[3] = { 255, 255, 255 };

SDL_Event event;
SDL_Window* displayWindow;
SDL_GLContext displayContext;

bool isRunning = true;

std::vector<SDL_Keycode> keyList;
bool backspacePress = false;
bool returnPress = false;
int mouseX, mouseY;
bool leftClickPress = false;
bool rightClickPress = false;

void update();
void render();
void drawLine(Vector2 a, Vector2 b, int color[3]);
void drawRect(Vector2 position, int width, int height, int color[3]);
bool checkKeyDown(SDL_Keycode Keycode);
Vector2 getProximity(Vector2 position);
void importData();
void exportData();

int main(int argc, char *argv[]) {
	displayWindow = SDL_CreateWindow("Mood Editor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 700, 700, SDL_WINDOW_OPENGL);
	displayContext = SDL_GL_CreateContext(displayWindow);
	glOrtho(-350, 350, 350, -350, 0, 1);
	
	TTF_Init();
	glEnable(GL_BLEND); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	while (isRunning) {
		backspacePress = false;
		returnPress = false;
		leftClickPress = false;
		rightClickPress = false;

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) { isRunning = false; }
			if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) { leftClickPress = true; }
			if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_RIGHT) { rightClickPress = true; }
			if (event.type == SDL_MOUSEMOTION) {
				mouseX = event.motion.x;
				mouseY = event.motion.y;
			}
			if (event.type == SDL_KEYDOWN) {
				if (std::find(keyList.begin(), keyList.end(), event.key.keysym.sym) == keyList.end()) {
					if (event.key.keysym.sym == SDLK_RETURN) {  returnPress = true; }
					else {
						if (event.key.keysym.sym == SDLK_BACKSPACE) { backspacePress = true; }
						else { keyList.push_back(event.key.keysym.sym); }
					}
				}
			}
			if (event.type == SDL_KEYUP) {
				keyList.erase(std::remove(keyList.begin(), keyList.end(), event.key.keysym.sym), keyList.end());
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
			tempWall.color[0] = colorPickerColor[0];
			tempWall.color[1] = colorPickerColor[1];
			tempWall.color[2] = colorPickerColor[2];

			wallList.push_back(tempWall);
			tempWall.pointA = { -1, -1 };
			tempWall.pointB = { -1, -1 };
		}
	}

	if (rightClickPress && wallList.size() > 0) { wallList.erase(wallList.end()); }

	if (checkKeyDown(SDLK_i) && colorPickerColor[0] < 255) { colorPickerColor[0] += 1; }
	if (checkKeyDown(SDLK_j) && colorPickerColor[0] > 0) { colorPickerColor[0] -= 1; }
	if (checkKeyDown(SDLK_o) && colorPickerColor[1] < 255) { colorPickerColor[1] += 1; }
	if (checkKeyDown(SDLK_k) && colorPickerColor[1] > 0) { colorPickerColor[1] -= 1; }
	if (checkKeyDown(SDLK_p) && colorPickerColor[2] < 255) { colorPickerColor[2] += 1; }
	if (checkKeyDown(SDLK_l) && colorPickerColor[2] > 0) { colorPickerColor[2] -= 1; }

	if (backspacePress) { importData(); }
	if (returnPress) { exportData(); }
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

	drawRect(colorPickerPosition, 50, 50, colorPickerColor);
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

void drawRect(Vector2 position, int width, int height, int color[3]) {
	Vector2 vectors[4]{
		{0, 0},
		{1, 0},
		{1, 1},
		{0, 1}
	};

	glBegin(GL_QUADS);
	glColor4f(convertColorFloatToRGB(color[0]), convertColorFloatToRGB(color[1]), convertColorFloatToRGB(color[2]), 1);
	for (int x = 0; x < 4; x++) {
		vectors[x].x *= width;
		vectors[x].y *= height;
		vectors[x].x += position.x;
		vectors[x].y += position.y;
		vectors[x].x -= 350.0;
		vectors[x].y -= 350.0;

		glVertex2d(vectors[x].x, vectors[x].y);
	}
	glEnd();
}

bool checkKeyDown(SDL_Keycode Keycode) {
	if (std::find(keyList.begin(), keyList.end(), Keycode) != keyList.end()) {
		return true;
	}

	return false;
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

std::vector<Vector2> getVerticesFromFile(const char* filename) {
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

std::vector<int> getColorsFromFile(const char* filename) {
	std::ifstream fin(filename);
	std::vector<int> color;

	int x;
	while (fin >> x) { color.push_back(x); }

	fin.close();

	return color;
}

void importData() {
	wallList.clear();
	std::vector<Vector2> positionList = getVerticesFromFile("map.data");
	std::vector<int> colorList = getColorsFromFile("color.data");

	for (int x = 0; x < positionList.size(); x += 2) {
		wallList.push_back({positionList[x], positionList[x + 1]});
	}

	for (int x = 0; x < wallList.size(); x++) {
		wallList[x].color[0] = colorList[(x * 3)];
		wallList[x].color[1] = colorList[(x * 3) + 1];
		wallList[x].color[2] = colorList[(x * 3) + 2];
	}
}

void exportData() {
	std::ofstream map("map.data"), color("color.data");

	for (Wall wall : wallList) {
		map << wall.pointA.x << " " << wall.pointA.y << " " << wall.pointB.x << " " << wall.pointB.y << " ";
		color << wall.color[0] << " " << wall.color[1] << " " << wall.color[2] << " ";
	}

	map.close(); color.close();
}