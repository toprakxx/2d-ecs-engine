#pragma once
#include "../ECS/ECS.h"
#include "../EventSystem/EventBus.hpp"
#include "../InputManager/InputManager.h"
#include "../Components/AnimationComponent.h"
#include "../Components/ColliderComponent.h"
#include "../Components/PlayerInventoryComponent.h"
#include "../Components/TransformComponent.h"
#include "../EventSystem/Events/TimerBridgeEvent.h"
#include "AnimationSystem.hpp"

class BridgeCrashSystem : public System {
public:
	void SubscribeToEvents(EventBus &eventBus, Registry *_registry) {
		eventBus.SubscribeToEvent(this, &BridgeCrashSystem::OnTimer);
		registry = _registry;
	}

	void OnTimer(TimerBridgeEvent &eaa) {
		auto entites = registry->u_GetEntitiesWithTag(Bridge);
		for (auto &e : *entites){
			auto &anim  = e.GetComponent<AnimationComponent>();
			ChangeAnimation(e, "crashed");
			Entity enew = registry->CreateEntity();
			auto &trans = e.GetComponent<TransformComponent>();
			enew.AddComponent<TransformComponent>(
				glm::vec2(trans.position),
				glm::vec2(SCALE_FACTOR_32)
			);
			enew.AddComponent<ColliderComponent>(
				Box,
				glm::vec2(0,0),
				32 * SCALE_FACTOR_32 * 3,
				32 * SCALE_FACTOR_32 * 3
			);
			enew.AddTag(Obstacle);
		}
	}

	Registry *registry = nullptr;
};
