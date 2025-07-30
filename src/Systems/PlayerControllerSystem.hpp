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
		RequireComponent<AnimationComponent>();
	}

	void Update(const InputManager& input) {
		int hAxis = 0;
		hAxis += input.isKeyDown(KEY_D) ? 1 : 0;
		hAxis -= input.isKeyDown(KEY_A) ? 1 : 0;
		for (auto e : GetSystemEntities()) {
			auto& rb = e.GetComponent<RigidBodyComponent>();
			const auto& pcc = e.GetComponent<PlayerControlComponent>();
			auto& anim = e.GetComponent<AnimationComponent>();

			rb.velocity.x = hAxis * pcc.playerSpeed;

			if(input.isKeyPressed(KEY_A)) ChangeAnimation(e, "WalkLeft");
			if(input.isKeyPressed(KEY_D)) ChangeAnimation(e, "WalkRight");
		}
	}
};
