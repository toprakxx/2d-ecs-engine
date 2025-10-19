#pragma once
#include "../ECS/ECS.h"
#include "../EventSystem/Events/CollisionEvent.h"
#include "../EventSystem/EventBus.hpp"
#include "../InputManager/InputManager.h"
#include "../Components/DarknessComponent.h"
#include "../Components/SpriteComponent.h"

class LeverSystem : public System {
public:
	void SubscribeToEvents(EventBus &eventBus, InputManager *_input, Registry *_registry) {
		eventBus.SubscribeToEvent(this, &LeverSystem::OnPlayerCast);
		input = _input;
		registry = _registry;
	}

	void OnPlayerCast(CollisionEvent &e) {
		if(!input) return;
		if(!input->isKeyDown(KEY_E)) return;

		if(e.a.HasTag(PlayerInteractionCast) and e.b.HasTag(Lever)
		or e.a.HasTag(Lever) and e.b.HasTag(PlayerInteractionCast)) {

			Entity interaction = e.a.HasTag(PlayerInteractionCast) ? e.a : e.b;
			Entity lever = e.a.HasTag(Lever) ? e.a : e.b;

			lever.GetComponent<SpriteComponent>().srcRect.x = 160;

			auto entities = registry->u_GetEntitiesWithTag(Obstacle);
			for (auto &e : *entities) {
				if (e.HasComponent<DarknessComponent>()) {
					e.Kill();
					return;
				}
			}
		}
	}

	InputManager *input = nullptr;
	Registry *registry = nullptr;
};
