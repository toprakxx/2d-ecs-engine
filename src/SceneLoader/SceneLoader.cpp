#include "SceneLoader.h"
#include "../Game/Game.h"
#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/AnimationComponent.h"
#include "../Components/TextComponent.h"
#include "../Components/PlayerControlComponent.h"
#include "../Components/UIButtonComponent.h"
#include "../Components/PipeSpawnerComponent.h"
#include "../Components/ColliderComponent.h"
#include "../Components/ScoreText.h"

auto &Registry =  Registry::registry;

void SceneLoader::UnloadCurrentScene() {
	Registry->ClearEntities();
}

void SceneLoader::LoadScene(Scenes level) {
	switch (level) {
	case StartMenu: {
			int midX = Game::windowWidth/2.0;
			SDL_Color white = {255, 255, 255};

			Entity title = Registry->CreateEntity();
			title.AddComponent<TransformComponent>(glm::vec2(midX, 300));
			title.AddComponent<TextComponent>("Jumpy Avian", "pico-80", white, TopCenter);

			Entity start = Registry->CreateEntity();
			start.AddComponent<TransformComponent>(glm::vec2(midX,500));
			start.AddComponent<TextComponent>("Start", "pico-40", white, TopCenter);
			start.AddComponent<UIButtonComponent>(200,50,[this](){
				UnloadCurrentScene();
				LoadScene(Gameplay);
			},glm::vec2(-100, 0));

			Entity quit = Registry->CreateEntity();
			quit.AddComponent<TransformComponent>(glm::vec2(midX,600));
			quit.AddComponent<TextComponent>("Quit", "pico-40", white, TopCenter);
			quit.AddComponent<UIButtonComponent>(200,50,[](){
				SDL_Event e;
				e.type = SDL_QUIT;
				SDL_PushEvent(&e);
			}, glm::vec2(-100,0));

			break;
		}
	case Gameplay:{
			//---//Player//---//
			int jumpSpeed = 300;
			int highGrav = 400;
			int lowGrav = 300;

			Entity bird = Registry->CreateEntity();
			bird.AddComponent<TransformComponent>(glm::vec2(Game::windowWidth/2 - 160,200), glm::vec2(10), 0.0);
			bird.AddComponent<SpriteComponent>("bird", 16, 16, 5);
			bird.AddComponent<AnimationComponent>(AnimationComponent{
				{"Idle",1,5},
				{"Flap", 0, 5, false},
				{"Dead", 2, 5}
			});
			bird.AddComponent<ColliderComponent>(Collider::Circle, glm::vec2(80,80), 100);
			bird.AddComponent<RigidBodyComponent>(glm::vec2(0,0), glm::vec2(0,0));
			bird.AddComponent<PlayerControlComponent>(-jumpSpeed, highGrav, lowGrav);
			bird.AddTag(Player);

			//---//Pipe Spawner//---//
			int gap = 300;
			int pipeRightShift = Game::windowWidth;
			int pipeMoveSpeed = 150;
			int high = Game::windowHeight/2 - 100;
			int low = Game::windowHeight - 140;
			double spawnTimer = 3;
			float pipeLifetime = 20;

			Entity pipeSpawner = Registry->CreateEntity();
			pipeSpawner.AddComponent<PipeSpawnerComponent>(gap, pipeRightShift, pipeMoveSpeed, high, low, spawnTimer, pipeLifetime);

			//---//Score//---//
			Entity text = Registry->CreateEntity();
			SDL_Color white = {255, 255, 255};
			text.AddComponent<TransformComponent>(glm::vec2(800, 50));
			text.AddComponent<TextComponent>("Score: ", "pico-40", white);
			text.AddComponent<ScoreText>();

			break;
		}
	case DeathScreen: {
			SDL_Color white = {255, 255, 255};
			SDL_Color red = {255, 0, 0};
			int midX = Game::windowWidth/2.0;

			// "You Died" text
			Entity deathText = Registry->CreateEntity();
			deathText.AddComponent<TransformComponent>(glm::vec2(midX, 350));
			deathText.AddComponent<TextComponent>("You Died", "pico-60", red, TopCenter);

			// Restart button
			Entity restart = Registry->CreateEntity();
			restart.AddComponent<TransformComponent>(glm::vec2(midX, 500));
			restart.AddComponent<TextComponent>("Restart", "pico-40", white, TopCenter);
			restart.AddComponent<UIButtonComponent>(300, 50, [this]() {
				UnloadCurrentScene();
				LoadScene(Gameplay);   // restart game
			}, glm::vec2(-150, 0));

			// Quit button
			Entity quit = Registry->CreateEntity();
			quit.AddComponent<TransformComponent>(glm::vec2(midX, 600));
			quit.AddComponent<TextComponent>("Quit", "pico-40", white, TopCenter);
			quit.AddComponent<UIButtonComponent>(200, 50, []() {
				SDL_Event e;
				e.type = SDL_QUIT;
				SDL_PushEvent(&e);
			}, glm::vec2(-100, 0));

			break;
		}
	}
}
