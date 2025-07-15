#include <cmath>
#include <iostream>
#include <SDL.h>
#include <iterator>
#include "./Game.h"
#include "SDL_pixels.h"
#include "SDL_render.h"
#include "SDL_video.h"

int Game::windowHeight;
int Game::windowWidth;

Game::Game() {
		std::cerr << "Game constructed." << std::endl;
}

Game::~Game() {
		std::cerr << "Game destructed." << std::endl;
}

void Game::Initalize() {
	if(SDL_Init(SDL_INIT_EVERYTHING)) {
		std::cerr << "Error initializing SDL." << std::endl;
	}

	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode(0, &displayMode);

	Game::windowWidth = 1920;
	// windowWidth = displayMode.w;
	// windowWidth = 2400;

	Game::windowHeight = 1080;
	// windowHeight = displayMode.h;
	// windowHeight = 1920;

	window = SDL_CreateWindow(
		NULL,
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
		std::cerr << "Error creating the SDL_Window." << std::endl;
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(!renderer) {
		std::cerr << "Error creating the SDL_Renderer." << std::endl;
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

}

void Game::ProcessInput() {

}

void Game::Update() {

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
