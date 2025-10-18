#include "SceneLoader.h"
#include "../ECS/ECS.h"
#include "../ECS/ECS.h"
#include "../Game/Game.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/PlayerControlComponent.h"
#include "../Components/ColliderComponent.h"
#include "../Components/AnimationComponent.h"

auto &Registry = Registry::registry;

void SceneLoader::UnloadCurrentScene() {
	Registry->ClearEntities();
}

inline int PseudoRandomTileOffset(int x, int y, int range) {
    unsigned h = x * 73856093u ^ y * 19349663u;
    return int(h % range);
}

void SceneLoader::LoadScene(Scenes level) {
	switch (level) {
	case StartMenu: {
			//---//EntityName//---//
			//Entity entity = Registry->CreateEntity();
			//entity.AddComponent<ComponentType>(args);

			const int SCALE_FACTOR_32 = 2;
			const int SCALE_FACTOR_16 = 10;

			//---//Player//---//
			Entity player = Registry->CreateEntity();
			player.AddComponent<TransformComponent>(
				glm::vec2(Game::windowWidth/2, Game::windowHeight/2),
				glm::vec2(SCALE_FACTOR_32)
			);
			player.AddComponent<SpriteComponent>("time-bot", 32, 32, 5);
			player.AddComponent<AnimationComponent>(AnimationComponent{
				{"IdleSouth", 0, 4, true, 6},
				{"WalkSouth", 1, 4, true, 6},
				{"IdleEast" , 2, 4, true, 6},
				{"WalkEast" , 3, 4, true, 6},
				{"IdleNorth", 4, 4, true, 6},
				{"WalkNorth", 5, 4, true, 6},
				{"IdleWest" , 6, 4, true, 6},
				{"WalkWest" , 7, 4, true, 6},
			});
			player.AddComponent<RigidBodyComponent>(
				glm::vec2(0,0)
			);
			player.AddComponent<PlayerControlComponent>(500.0);
			player.AddComponent<ColliderComponent>(
				Box,
				glm::vec2(0,0),
				32 * SCALE_FACTOR_32,
				32 * SCALE_FACTOR_32
			);
			player.AddTag(Player);

			//---//Wall//---//
			Entity wall = Registry->CreateEntity();
			wall.AddComponent<TransformComponent>(
				glm::vec2(Game::windowWidth/2 + 100, Game::windowHeight/2 + 100),
				glm::vec2(SCALE_FACTOR_32)
			);
			wall.AddComponent<SpriteComponent>("metal-ground", 32, 32, 5, false, 32*5, 0);
			wall.AddComponent<ColliderComponent>(
				Box,
				glm::vec2(0,0),
				32 * SCALE_FACTOR_32,
				32 * SCALE_FACTOR_32
			);
			wall.AddTag(Obstacle);

			//---//Ground//---//
			for (int y = 0; y < 640; y += 64){
				for (int x = 0; x < 640; x += 64) {
					Entity tile = Registry->CreateEntity();
					tile.AddComponent<TransformComponent>(
						glm::vec2(x, y),
						glm::vec2(SCALE_FACTOR_32)
					);
					tile.AddComponent<SpriteComponent>("metal-ground", 32, 32, 0, false, 32*PseudoRandomTileOffset(x, y, 5), 0);
				}
			}

			break;
		}
	case Gameplay:{

			break;
		}
	case DeathScreen: {

			break;
		}
	}
}
