#pragma once
#include <random>
#include "../ECS/ECS.h"
#include "../Components/PipeSpawnerComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/ColliderComponent.h"

class PipeSpawnSystem : public System {
public:
	PipeSpawnSystem() {
		RequireComponent<PipeSpawnerComponent>();
	}

	void Update(double deltaTime) {
		for (auto& e : GetSystemEntities()) {
			auto& psc = e.GetComponent<PipeSpawnerComponent>();

			psc.currentTimer -= deltaTime;
			if (psc.currentTimer > 0) continue;
			psc.currentTimer = psc.spawnTimer;

			std::uniform_int_distribution<int> dist (psc.high, psc.low);
			int random = dist(rng);

			Entity bottom = Registry::registry->CreateEntity();
			bottom.AddComponent<SpriteComponent>("blue-man", 16, 16);
			bottom.AddComponent<TransformComponent>(glm::vec2(psc.pipeRightShift, random), glm::vec2(10));
			bottom.AddComponent<ColliderComponent>(Collider::Box, glm::vec2(0), 160, 160);
			bottom.AddComponent<RigidBodyComponent>(glm::vec2(-psc.pipeMoveSpeed, 0));
			bottom.AddTag(Obstacle);

			Entity top = Registry::registry->CreateEntity();
			top.AddComponent<SpriteComponent>("blue-man", 16, 16);
			int offset = top.GetComponent<SpriteComponent>().height;
			top.AddComponent<TransformComponent>(glm::vec2(psc.pipeRightShift, random - (offset*10 + psc.gap)), glm::vec2(10));
			top.AddComponent<ColliderComponent>(Collider::Box, glm::vec2(0), 160, 160);
			top.AddComponent<RigidBodyComponent>(glm::vec2(-psc.pipeMoveSpeed, 0));
			top.AddTag(Obstacle);

			int scoreYPos = bottom.GetComponent<TransformComponent>().position.y - psc.gap + 10;
			Entity score = Registry::registry->CreateEntity();
			score.AddComponent<TransformComponent>(glm::vec2(psc.pipeRightShift + 30, scoreYPos));
			score.AddComponent<ColliderComponent>(Box, glm::vec2(0), 100, psc.gap - 20);
			score.AddComponent<RigidBodyComponent>(glm::vec2(-psc.pipeMoveSpeed, 0));
			score.AddTag(Score);
		}
	}

private:
	std::mt19937 rng {std::random_device{}()};
};
