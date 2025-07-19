#include <SDL.h>
#include "./Game.h"
#include "../Logger/Logger.h"

int Game::windowHeight;
int Game::windowWidth;

Game::Game() {
	Logger::Confirm("Game constructed.");
}

Game::~Game() {
	Logger::Confirm("Game destructed.");
}

void Game::Initalize() {
	SDL_SetHint(SDL_HINT_WINDOWS_DPI_AWARENESS, "permonitorv2");
	if(SDL_Init(SDL_INIT_EVERYTHING)) {
		Logger::Err("Error initializing SDL.");
	}

	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode(0, &displayMode);
	printf("SDL sees desktop as %dx%d\n", displayMode.w, displayMode.h);

	windowWidth = 1920;
	//windowWidth = displayMode.w;

	windowHeight = 1080;
	//windowHeight = displayMode.h;

	window = SDL_CreateWindow(
		"Game",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		windowWidth,
		windowHeight,
		// SDL_WINDOW_FULLSCREEN,
		// SDL_WINDOW_BORDERLESS,
		// SDL_WINDOW_RESIZABLE,
		0
	);
	if(!window) {
		Logger::Err("Error creating the SDL_Window.");
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(!renderer) {
		Logger::Err("Error creating the SDL_Renderer.");
		return;
	}

	isGameRunning = true;
}

void Game::Run() {
	SetUp();
	while(isGameRunning) {
		ProcessInput();
		Update();
		Render();
	}
}

void Game::SetUp() {
	Entity test = registry.CreateEntity();
	assetManager.AddTexture(renderer, "test-dummy", "./images/test.jpeg");
}

void Game::ProcessInput() {
	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent)) {
		//SDL Core inputs
		switch (sdlEvent.type) {
		case SDL_QUIT:
			isGameRunning = false;
			break;
		}
	}
}

void Game::Update() {
	// int timeToWait = MIN_MS_PER_FRAME - (SDL_GetTicks64() - msPassedUntilLastFrame);
	// if (timeToWait > 0 && timeToWait <= MIN_MS_PER_FRAME) {
	// 	SDL_Delay(timeToWait);
	// }

	//Time passed between last and this frame. (Converted from ms to seconds)
	deltaTime = (SDL_GetTicks64() - msPassedUntilLastFrame) / 1000.0f;
	msPassedUntilLastFrame = SDL_GetTicks64();
}

void Game::Render() {
	SDL_SetRenderDrawColor(renderer, 76, 187, 32, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);
}

void Game::Destroy() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
