#include <SDL.h>
#include <glm/glm.hpp>
#include "./Game.h"
#include "../Logger/Logger.h"

#include "../Systems/RenderSystem.hpp"
#include "../Systems/MovementSystem.hpp"
#include "../Systems/AnimationSystem.hpp"
#include "../Systems/CollisionSystem.hpp"
#include "../Systems/DamageSystem.hpp" //Update free, subscriber
#include "../Systems/CollisionDebugSystem.hpp"
#include "../Systems/CameraFollowSystem.hpp"

#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/AnimationComponent.h"
#include "../Components/CameraFollowComponent.h"

int Game::windowHeight;
int Game::windowWidth;

Game::Game() {
	Logger::Confirm("Game constructed.");
}

Game::~Game() {
	Logger::Confirm("Game destructed.");
}

void Game::Initalize() {
	//Resolution awareness
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
		// SDL_WINDOW_FULLSCREEN
		SDL_WINDOW_BORDERLESS
		// SDL_WINDOW_RESIZABLE
		// 0
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

	//Initalizing the camera
	camera.x = 0;
	camera.y = 0;
	camera.w = windowWidth;
	camera.h = windowHeight;

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
	registry.AddSystem<DamageSystem>();
	registry.AddSystem<CollisionSystem>();
	registry.AddSystem<CollisionDebugSystem>();
	registry.AddSystem<CameraFollowSystem>();

	registry.GetSystem<DamageSystem>().SubscribeToEvents(eventBus);

	Entity test = registry.CreateEntity();
	test.AddTag(Tag::Player);
	test.AddComponent<TransformComponent>(glm::vec2(350.0,350.0), glm::vec2(10), 0.0);
	test.AddComponent<SpriteComponent>("blue-man-walk-right",16,16);
	test.AddComponent<RigidBodyComponent>(glm::vec2(100,0));
	test.AddComponent<AnimationComponent>(8);
	test.AddComponent<BoxColliderComponent>(160, 160);
	test.AddComponent<CameraFollowComponent>();

	Entity obs = registry.CreateEntity();
	obs.AddComponent<TransformComponent>(glm::vec2(750.0,350.0), glm::vec2(10), 0.0);
	obs.AddComponent<SpriteComponent>("blue-man",16,16);
	obs.AddComponent<BoxColliderComponent>(160, 160);
}

void Game::ProcessInput() {
	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent)) {
		//SDL Core inputs
		switch (sdlEvent.type) {
		case SDL_QUIT:
			isGameRunning = false;
			break;
		case SDL_KEYDOWN:
			if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) isGameRunning = false;
			if (sdlEvent.key.keysym.sym == SDLK_F1) inDebugMode = !inDebugMode;
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
	registry.GetSystem<CollisionSystem>().Update(eventBus);
	registry.GetSystem<CameraFollowSystem>().Update(camera);
	
	//Time passed between last and this frame. (Converted from ms to seconds)
	deltaTime = (SDL_GetTicks64() - msPassedUntilLastFrame) / 1000.0f;
	msPassedUntilLastFrame = SDL_GetTicks64();
}

void Game::Render() {
	SDL_SetRenderDrawColor(renderer, 76, 187, 32, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	registry.GetSystem<RenderSystem>().Update(renderer, assetManager, camera);
	registry.GetSystem<CollisionDebugSystem>().Update(renderer, inDebugMode, camera);

	SDL_RenderPresent(renderer);
}

void Game::Destroy() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
