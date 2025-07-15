#pragma once
#include "SDL_render.h"
#include <SDL.h>

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
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
};
