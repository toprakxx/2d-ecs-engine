#pragma once
#include <SDL.h>
#include "../ECS/ECS.h"
#include "../AssetManager/AssetManager.h"
#include "../EventSystem/EventBus.hpp"

const int MAX_FPS = 160;
const int MIN_MS_PER_FRAME = 1000 / MAX_FPS;

class Game {
public:
	Game();
	~Game();
	void Initalize();
	void Run();
	void SetUp();
	void ProcessInput();
	void Update();
	void Render();
	void Destroy();

	static int windowWidth;
	static int windowHeight;

private:
	bool isGameRunning = false;
	bool inDebugMode = false;

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	int msPassedUntilLastFrame = 0;
	double deltaTime = 0;

	Registry registry;
	AssetManager assetManager;
	EventBus eventBus;
	SDL_Rect camera;
};
