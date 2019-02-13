#include "engine.h"

void Engine::initialize() {
	configuration.initialize();

	displayWindow = SDL_CreateWindow("Mood", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, configuration.getScreenWidth(), configuration.getScreenHeight(), SDL_WINDOW_OPENGL);
	displayContext = SDL_GL_CreateContext(displayWindow);
	glOrtho(-configuration.getScreenWidth() / 2, configuration.getScreenWidth() / 2, configuration.getScreenHeight() / 2, -configuration.getScreenHeight() / 2, 0, 1);

	TTF_Init();

	initializeWindowHandle();
	initializeAudio();

	initializeExternalController();

	enableBlendAlpha();
	seedRandom();

	joiner.initialize();
}

void Engine::initializeWindowHandle() {
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(displayWindow, &wmInfo);
	hwnd = wmInfo.info.win.window;
}

void Engine::initializeAudio() {
	audio.initialize(hwnd);
}

void Engine::initializeExternalController() {
	SDL_Init(SDL_INIT_GAMECONTROLLER);
	input.setupController();	
}

void Engine::enableBlendAlpha() {
	glEnable(GL_BLEND); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Engine::seedRandom() {
	joiner.seed = time(NULL);
	srand(joiner.seed);
}

void Engine::start() {
	while (isRunning) {
		handleEvents();
		delayEarlyFrames();
		updateAndRender();
	}
}

void Engine::quit() {
	SDL_Quit();
	audio.quit();
}

void Engine::handleEvents() {
	input.clearExpiredInput();

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			isRunning = false;
		}

		handleUserInput();
	}
}

void Engine::handleUserInput() {
	input.getKeyTrigger(event);
	input.getMouseTrigger(event);
}

void Engine::delayEarlyFrames() {
	//TODO: change to regulate FPS
	
	if (deltaTime < 1 / 60) {
		frameStart = SDL_GetTicks();
		SDL_Delay(1);
		frameEnd = SDL_GetTicks();
		deltaTime = frameEnd - frameStart;
	}
}

void Engine::updateAndRender() {
	frameStart = SDL_GetTicks();
	update();
	render();
	frameEnd = SDL_GetTicks();
	deltaTime = frameEnd - frameStart; 
}

void Engine::update() {
	//handleEscapeKey();
	timer.setTime(deltaTime);
	joiner.update();
}

void Engine::handleEscapeKey() {
	if (input.checkKeyDown(SDLK_ESCAPE)) {
		isRunning = false;
	}
}

void Engine::render() {
	SDL_GL_MakeCurrent(displayWindow, displayContext);
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	joiner.draw();
	glPopMatrix();

	SDL_GL_SwapWindow(displayWindow);
}