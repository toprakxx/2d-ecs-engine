#include "LevelLoader.h"
#include "../Game/Game.h"
#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/AnimationComponent.h"
#include "../Components/CameraFollowComponent.h"
#include "../Components/TextComponent.h"
#include "../Components/PlayerControlComponent.h"
#include "../Components/UIButtonComponent.h"
#include "../Components/PipeSpawnerComponent.h"
#include "../Components/ColliderComponent.h"
#include "../Components/ScoreText.h"

void LevelLoader::UnloadCurrentLevel() {
	Registry::registry->ClearEntities();
}

void LevelLoader::LoadLevel(Levels level) {
	UnloadCurrentLevel();

	switch (level) {
	case StartMenu: 
	case Gameplay:{
		//---//Player//---//
		int jumpSpeed = 300;
		int highGrav = 400;
		int lowGrav = 300;

		Entity bird = Registry::registry->CreateEntity();
		bird.AddComponent<TransformComponent>(glm::vec2(Game::windowWidth/2 - 160,0), glm::vec2(10), 0.0);
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

		Entity pipeSpawner = Registry::registry->CreateEntity();
		pipeSpawner.AddComponent<PipeSpawnerComponent>(gap, pipeRightShift, pipeMoveSpeed, high, low, spawnTimer);

		//---//Score//---//
		Entity text = Registry::registry->CreateEntity();
		SDL_Color white = {255, 255, 255};
		text.AddComponent<TextComponent>(glm::vec2(800.0, 50.0),"Press F1", "pico-40", white, true);
		text.AddComponent<ScoreText>();

		break;
	}
		break;
	case DeathScreen:
		break;
	}
}
