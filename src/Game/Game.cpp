#include <SDL.h>
#include <glm/glm.hpp>
#include "./Game.h"
#include "../Logger/Logger.h"
#include "../Systems/RenderSystem.hpp"
#include "../Systems/MovementSystem.hpp"
#include "../Systems/AnimationSystem.hpp"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/AnimationComponent.h"

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
	assetManager.AddTexture(renderer, "blue-man", "./images/blue-man0.png");
	assetManager.AddTexture(renderer, "blue-man-walk-right", "./images/blue-man-walk-sheet.png");

	registry.AddSystem<RenderSystem>();
	registry.AddSystem<MovementSystem>();
	registry.AddSystem<AnimationSystem>();
	
	Entity test = registry.CreateEntity();
	test.AddComponent<TransformComponent>(glm::vec2(350.0,350.0), glm::vec2(1.0, 1.0), 0.0);
	test.AddComponent<SpriteComponent>("blue-man-walk-right",16,16,10);
	test.AddComponent<RigidBodyComponent>(glm::vec2(100,0));
	test.AddComponent<AnimationComponent>(8);
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
	//Limiting the FPS
	// int timeToWait = MIN_MS_PER_FRAME - (SDL_GetTicks64() - msPassedUntilLastFrame);
	// if (timeToWait > 0 && timeToWait <= MIN_MS_PER_FRAME) {
	// 	SDL_Delay(timeToWait);
	// }

	registry.Update();

	registry.GetSystem<MovementSystem>().Update(deltaTime);
	registry.GetSystem<AnimationSystem>().Update(deltaTime);
	
	//Time passed between last and this frame. (Converted from ms to seconds)
	deltaTime = (SDL_GetTicks64() - msPassedUntilLastFrame) / 1000.0f;
	msPassedUntilLastFrame = SDL_GetTicks64();
}

void Game::Render() {
	SDL_SetRenderDrawColor(renderer, 76, 187, 32, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	registry.GetSystem<RenderSystem>().Update(renderer, assetManager);

	SDL_RenderPresent(renderer);
}

void Game::Destroy() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
