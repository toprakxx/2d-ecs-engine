#pragma once
#include "../ECS/ECS.h"
#include "../EventSystem/EventBus.hpp"
#include "../InputManager/InputManager.h"
#include "../Components/DoorComponent.h"
#include "../Components/PlayerInventoryComponent.h"
#include "../Components/AnimationComponent.h"
#include "../EventSystem/Events/CollisionEvent.h"
#include "../EventSystem/Events/SoundEffectEvent.h"
#include "AnimationSystem.hpp"

class DoorSystem : public System {
public:
	void SubscribeToEvents(EventBus &eventBus, InputManager *_input) {
		eventBus.SubscribeToEvent<DoorSystem, CollisionEvent>(this, &DoorSystem::OnPlayerCast);
		input = _input;
		eb = &eventBus;
	}

	void OnPlayerCast(CollisionEvent &e) {
		if(!input) return;
		if(!input->isKeyDown(KEY_E)) return;

		if(e.a.HasTag(PlayerInteractionCast) and e.b.HasTag(Obstacle)
		or e.a.HasTag(Obstacle) and e.b.HasTag(PlayerInteractionCast)) {

			Entity interaction = e.a.HasTag(PlayerInteractionCast) ? e.a : e.b;
			Entity door = e.a.HasTag(Obstacle) ? e.a : e.b;
			if(!door.HasComponent<DoorComponent>()) return;

			const auto &inventory = interaction.GetComponent<PlayerInventoryComponent>();
			const auto &doorComponent = door.GetComponent<DoorComponent>();

			switch (doorComponent.doorId) {
			case CardDoor:
				if(inventory.hasCard) door.Kill();
				break;
			case KeyDoor:
				if(inventory.hasKey) door.Kill();
				break;
			case BombDoor:
				if(inventory.hasBomb) {
						door.Kill();
						eb->EmitEvent<SoundEffectEvent>("explosion");
						// ChangeAnimation(door, "boom");
					}
				break;
			}
		}
	}

	InputManager* input = nullptr;
	EventBus *eb = nullptr;
};
