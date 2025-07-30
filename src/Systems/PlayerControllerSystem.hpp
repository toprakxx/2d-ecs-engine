#pragma once
#include "../ECS/ECS.h"
#include "../InputManager/InputManager.h"
#include "../Systems/AnimationSystem.hpp"
#include "../Components/PlayerControlComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/AnimationComponent.h"

class PlayerControllerSystem : public System {
public:
	PlayerControllerSystem() {
		RequireComponent<PlayerControlComponent>();
		RequireComponent<TransformComponent>();
		RequireComponent<RigidBodyComponent>();
	}

	void Update(const InputManager& input) {
		for (auto e : GetSystemEntities()) {
			auto& rb = e.GetComponent<RigidBodyComponent>();
			const auto& pcc = e.GetComponent<PlayerControlComponent>();

			if(input.isKeyPressed(KEY_SPACE)) rb.velocity.y = pcc.jumpSpeed;
		}
	}
};
