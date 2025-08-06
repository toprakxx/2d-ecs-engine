#pragma once
#include "../ECS/ECS.h"
#include "../Game/Game.h"
#include "../InputManager/InputManager.h"
#include "../Systems/AnimationSystem.hpp"
#include "../Components/PlayerControlComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../EventSystem/Events/SoundEffectEvent.h"

class PlayerControllerSystem : public System {
public:
	PlayerControllerSystem() {
		RequireComponent<PlayerControlComponent>();
		RequireComponent<TransformComponent>();
		RequireComponent<RigidBodyComponent>();
	}

	void Update(const InputManager& input, SceneLoader& sceneLoader, EventBus& eb) {
		for (auto e : GetSystemEntities()) {
			auto& rb = e.GetComponent<RigidBodyComponent>();
			auto& pcc = e.GetComponent<PlayerControlComponent>();
			const auto& transform = e.GetComponent<TransformComponent>();

			if(input.isKeyPressed(KEY_SPACE) and pcc.isAlive) {
				rb.velocity.y = pcc.jumpSpeed;
				ChangeAnimation(e, "Flap");
				eb.EmitEvent<SoundEffectEvent>("jump-sound");
			}

			if(rb.velocity.y >= 0) {
				//Going down
				rb.acceleration.y = pcc.highGrav;
			} else {
				//Going up
				rb.acceleration.y = pcc.lowGrav;
			}

			if(transform.position.y > Game::windowHeight and pcc.isAlive) {
				pcc.isAlive = false;
				ChangeAnimation(e, "Dead");
				sceneLoader.LoadScene(DeathScreen);
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
