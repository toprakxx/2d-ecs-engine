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

			if(input.isKeyPressed(KEY_SPACE)) {
				rb.velocity.y = pcc.jumpSpeed;
				ChangeAnimation(e, "Flap");
			}

			if(rb.velocity.y >= 0) {
				//Going down
				rb.acceleration.y = pcc.highGrav;
			} else {
				//Going up
				rb.acceleration.y = pcc.lowGrav;
			}
		}
	}

	void SubscribeToEvents(EventBus& eventBus) {
		eventBus.SubscribeToEvent<PlayerControllerSystem, AnimationDoneEvent>(
			this, &PlayerControllerSystem::OnAnimationDone
		);
	}

	void OnAnimationDone(AnimationDoneEvent& event) {
		if(event.animationName == "Flap") ChangeAnimation(event.entity, "Idle");
	}
};
