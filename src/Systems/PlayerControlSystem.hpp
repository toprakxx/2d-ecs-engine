#pragma once
#include "../ECS/ECS.h"
#include "../InputManager/InputManager.h"
#include "../Components/TransformComponent.h"
#include "../Components/PlayerControlComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "glm/geometric.hpp"

class PlayerControlSystem : public System {
public:
	PlayerControlSystem() {
		RequireComponent<TransformComponent>();
		RequireComponent<RigidBodyComponent>();
		RequireComponent<PlayerControlComponent>();
	}

	void Update(const InputManager &input) {
		for (auto& e : GetSystemEntities()) {
			auto& playerRB = e.GetComponent<RigidBodyComponent>();
			auto& playerController = e.GetComponent<PlayerControlComponent>();

			int x = 0;
			x = (input.isKeyDown(KEY_D) * 1) + (input.isKeyDown(KEY_A) * -1);
			int y = 0;
			y += (input.isKeyDown(KEY_S) * 1) + (input.isKeyDown(KEY_W) * -1);

			glm::vec2 movementVector(x,y);
			if(movementVector != glm::vec2(0))
				playerRB.velocity = glm::normalize(movementVector)* playerController.moveSpeed;
			else
				playerRB.velocity = glm::vec2(0);
		}
	}
};
