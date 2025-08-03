#include <SDL.h>
#include <glm/glm.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl2.h>
#include <imgui/imgui_impl_sdlrenderer2.h>
#include "../Utils.hpp"
#include "./Game.h"
#include "../Logger/Logger.h"
#include "../SceneLoader/SceneLoader.h"

#include "../Systems/RenderSystem.hpp"
#include "../Systems/MovementSystem.hpp"
#include "../Systems/AnimationSystem.hpp"
#include "../Systems/CollisionSystem.hpp"
#include "../Systems/DamageSystem.hpp" //Update free, subscriber
#include "../Systems/CollisionDebugSystem.hpp"
#include "../Systems/CameraFollowSystem.hpp"
#include "../Systems/TextRenderSystem.hpp"
#include "../Systems/ImGuiRenderSystem.hpp"
#include "../Systems/PlayerControllerSystem.hpp"
#include "../Systems/UIButtonSystem.hpp"
#include "../Systems/PipeSpawnSystem.hpp"
#include "../Systems/ScoreUpdateSystem.hpp"
#include "../Systems/PipeCollisionSytem.hpp"
#include "../Systems/UIDebugSystem.hpp"
#include "../Systems/LifetimeSystem.hpp"

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

	if (TTF_Init() != 0) {
		Logger::Err("Error initializing TTF");
		return;
	}

	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode(0, &displayMode);
	printf("SDL sees desktop as %dx%d\n", displayMode.w, displayMode.h);

	windowWidth = 1920;
	// windowWidth = 960;
	//windowWidth = displayMode.w;

	windowHeight = 1080;
	// windowHeight = 540;
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

	//Setting up ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.FontGlobalScale = 2.0f;
	ImGui::GetStyle().ScaleAllSizes(2.0f);
	ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer2_Init(renderer);
	

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
	assetManager.AddTexture(renderer, "blue-man", "blue-man0.png");
	assetManager.AddTexture(renderer, "blue-man-walk", "blue-man-walk-sheet.png");
	assetManager.AddTexture(renderer, "bird", "blue-bird-sheet.png");
	assetManager.AddTexture(renderer, "bottom-pipe", "bottom-pipe.png");
	assetManager.AddTexture(renderer, "top-pipe", "top-pipe.png");

	assetManager.AddFont("arial-40", "arial.ttf", 40);
	assetManager.AddFont("pico-40", "pico8.ttf", 40);
	assetManager.AddFont("pico-60", "pico8.ttf", 60);
	assetManager.AddFont("pico-80", "pico8.ttf", 80);

	registry.AddSystem<RenderSystem>();
	registry.AddSystem<MovementSystem>();
	registry.AddSystem<AnimationSystem>();
	registry.AddSystem<DamageSystem>();
	registry.AddSystem<CollisionSystem>();
	registry.AddSystem<CollisionDebugSystem>();
	registry.AddSystem<CameraFollowSystem>();
	registry.AddSystem<TextRenderSystem>();
	registry.AddSystem<ImGuiRenderSystem>();
	registry.AddSystem<PlayerControllerSystem>();
	registry.AddSystem<UIButtonSystem>();
	registry.AddSystem<PipeSpawnSystem>();
	registry.AddSystem<ScoreUpdateSystem>();
	registry.AddSystem<PipeCollisionSystem>();
	registry.AddSystem<UIDebugSystem>();
	registry.AddSystem<LifetimeSystem>();

	sceneLoader.LoadScene(Scenes::StartMenu);

	//Systems that subscribe to events do so here
	registry.GetSystem<DamageSystem>().SubscribeToEvents(eventBus);
	registry.GetSystem<PlayerControllerSystem>().SubscribeToEvents(eventBus);
	registry.GetSystem<ScoreUpdateSystem>().SubscribeToEvents(eventBus);
	registry.GetSystem<PipeCollisionSystem>().SubscribeToEvents(eventBus, &sceneLoader);

}

void Game::ProcessInput() {
	SDL_Event sdlEvent;
	inputManager.BeginFrame();
	while (SDL_PollEvent(&sdlEvent)) {
		ImGui_ImplSDL2_ProcessEvent(&sdlEvent);

		//SDL Core inputs
		switch (sdlEvent.type) {
		case SDL_QUIT:
			isGameRunning = false;
			break;
		case SDL_KEYDOWN:
			if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
				isGameRunning = false;
				// registry.ClearEntities();
			}
			if (sdlEvent.key.keysym.sym == SDLK_F1) inDebugMode = !inDebugMode;
			inputManager.KeyPressed(sdlEvent.key.keysym.scancode);
			break;
		case SDL_KEYUP:
			inputManager.KeyReleased(sdlEvent.key.keysym.scancode);
			break;
		case SDL_MOUSEBUTTONDOWN:
			inputManager.MousePressed(sdlEvent.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			inputManager.MouseReleased(sdlEvent.button.button);
			break;
		case SDL_MOUSEMOTION:
			inputManager.SetMousePosition(sdlEvent.motion.x, sdlEvent.motion.y);
		}
	}
	//System dependent on input get updated here
	registry.GetSystem<PlayerControllerSystem>().Update(inputManager, sceneLoader);
	registry.GetSystem<UIButtonSystem>().Update(eventBus, camera, inputManager);
}

void Game::Update() {
	//Limiting the FPS
	int timeToWait = MIN_MS_PER_FRAME - (SDL_GetTicks64() - msPassedUntilLastFrame);
	if (timeToWait > 0 && timeToWait <= MIN_MS_PER_FRAME) {
		SDL_Delay(timeToWait);
	}

	registry.Update();

	registry.GetSystem<MovementSystem>().Update(deltaTime);
	registry.GetSystem<AnimationSystem>().Update(deltaTime, eventBus);
	registry.GetSystem<CollisionSystem>().Update(eventBus);
	registry.GetSystem<CameraFollowSystem>().Update(camera);
	registry.GetSystem<PipeSpawnSystem>().Update(deltaTime);
	registry.GetSystem<ScoreUpdateSystem>().Update();
	registry.GetSystem<LifetimeSystem>().Update(deltaTime);
	
	//Time passed between last and this frame. (Converted from ms to seconds)
	deltaTime = (SDL_GetTicks64() - msPassedUntilLastFrame) / 1000.0f;
	msPassedUntilLastFrame = SDL_GetTicks64();
}

void Game::Render() {
	SDL_Color background = {150, 150, 0, SDL_ALPHA_OPAQUE};
	SDL_SetRenderDrawColor(renderer, background.r, background.g, background.b , background.a);
	SDL_RenderClear(renderer);

	//Systems dependent on rendering get updated here
	registry.GetSystem<RenderSystem>().Update(renderer, assetManager, camera);
	registry.GetSystem<TextRenderSystem>().Update(renderer, assetManager, camera);

	if(inDebugMode) {
		registry.GetSystem<CollisionDebugSystem>().Update(renderer, camera);
		registry.GetSystem<ImGuiRenderSystem>().Update(renderer, camera, registry, deltaTime);
		registry.GetSystem<UIDebugSystem>().Update(renderer, camera);
	}

	SDL_RenderPresent(renderer);
}

void Game::Destroy() {
	ImGui_ImplSDLRenderer2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void LoadGameplay() {
}
