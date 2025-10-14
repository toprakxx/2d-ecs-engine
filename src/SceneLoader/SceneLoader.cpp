#include "SceneLoader.h"
#include "../ECS/ECS.h"
#include "../Game/Game.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/ParentComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/PlayerControlComponent.h"

auto &Registry = Registry::registry;

void SceneLoader::UnloadCurrentScene() {
	Registry->ClearEntities();
}

void SceneLoader::LoadScene(Scenes level) {
	switch (level) {
	case StartMenu: {
			//---//EntityName//---//
			//Entity entity = Registry->CreateEntity();
			//entity.AddComponent<ComponentType>(args);

			//---//Pipe//---//
			Entity pipe = Registry->CreateEntity();
			pipe.AddComponent<TransformComponent>(
				glm::vec2(0,0),
				glm::vec2(3)
			);
			pipe.AddComponent<SpriteComponent>("pipe", 16, 32, 10);
			
			//---//Player//---//
			Entity player = Registry->CreateEntity();
			player.AddComponent<TransformComponent>(
				glm::vec2(Game::windowWidth/2, Game::windowHeight/2),
				glm::vec2(10)
			);
			player.AddComponent<SpriteComponent>("blue-man", 16, 16, 5);
			player.AddComponent<RigidBodyComponent>(
				glm::vec2(0,0)
			);
			player.AddComponent<PlayerControlComponent>(500);
			player.AddComponent<ParentComponent>(ParentComponent{
				{pipe, glm::vec2(90,10)}
			});
			player.AddTag(Player);

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
