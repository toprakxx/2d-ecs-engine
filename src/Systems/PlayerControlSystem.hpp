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

			int x = (input.isKeyDown(KEY_D) ? 1 : 0) - (input.isKeyDown(KEY_A) ? 1 : 0);
			int y = (input.isKeyDown(KEY_S) ? 1 : 0) - (input.isKeyDown(KEY_W) ? 1 : 0);

			glm::vec2 movementVector(x,y);
			PlayerState newState = playerController.state;

			// if(movementVector != glm::vec2(0))
			// 	playerRB.velocity = glm::normalize(movementVector) * playerController.playerMoveSpeed;
			// else
			// 	playerRB.velocity = glm::vec2(0);

			if (movementVector != glm::vec2(0)) {
				playerRB.velocity = glm::normalize(movementVector) * playerController.playerMoveSpeed;

				if (std::abs(playerRB.velocity.x) > std::abs(playerRB.velocity.y)) {
					newState = (playerRB.velocity.x > 0) ? WALK_EAST : WALK_WEST;
				} else {
					newState = (playerRB.velocity.y > 0) ? WALK_SOUTH : WALK_NORTH;
				}
			} else {
				playerRB.velocity = glm::vec2(0);
				switch (playerController.state) {
					case WALK_NORTH: newState = IDLE_NORTH; break;
					case WALK_SOUTH: newState = IDLE_SOUTH; break;
					case WALK_EAST:  newState = IDLE_EAST;  break;
					case WALK_WEST:  newState = IDLE_WEST;  break;
					default: break;
				}
			}
			playerController.state = newState;
		}
	}
};
