#pragma once
#include "../ECS/ECS.h"
#include "../EventSystem/EventBus.hpp"
#include "../InputManager/InputManager.h"
#include "../Components/CollectibleComponent.h"
#include "../Components/PlayerInventoryComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/PasswordManagerComponent.h"
#include "../Components/ColliderComponent.h"
#include "../Components/BigDoorComponent.h"
#include "../Components/ControlPanelComponent.h"
#include "../EventSystem/Events/CollisionEvent.h"
#include <iostream>
#include <ostream>

class ControlPanelSystem : public System {
public:
	void SubscribeToEvents(EventBus &eventBus, InputManager *_input, Registry *_registry) {
		eventBus.SubscribeToEvent(this, &ControlPanelSystem::OnPlayerCast);
		input = _input;
		registry = _registry;
	}

	void OnPlayerCast(CollisionEvent &e) {
		if(!input) return;
		if(!input->isKeyDown(KEY_E)) return;

		if(e.a.HasTag(PlayerInteractionCast) and e.b.HasTag(Obstacle)
		or e.a.HasTag(Obstacle) and e.b.HasTag(PlayerInteractionCast)) {

			Entity interaction = e.a.HasTag(PlayerInteractionCast) ? e.a : e.b;
			Entity panel = e.a.HasTag(Obstacle) ? e.a : e.b;
			if(!panel.HasComponent<ControlPanelComponent>()) return;
			int numDigits;
			auto entities = registry->u_GetEntitiesWithTag(PasswordManager);
			for (auto &e : *entities) {
				numDigits = e.GetComponent<PasswordManagerComponent>().numKnownDigits;
			}

			auto &sprite = panel.GetComponent<SpriteComponent>();
			sprite.srcRect.x = 32 * numDigits;

			if(numDigits == 3) {
				auto entities = registry->u_GetEntitiesWithTag(Obstacle);
				for (auto &e : *entities) {
					if (e.HasComponent<BigDoorComponent>()) {
						std::cout << "test" << std::endl;
						// e.RemoveComponent<ColliderComponent>();
						e.Kill();
						return;
					}
				}
			}
		}
	}

	InputManager *input = nullptr;
	Registry *registry = nullptr;
};
