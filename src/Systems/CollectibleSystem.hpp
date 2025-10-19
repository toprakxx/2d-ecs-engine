#pragma once
#include "../ECS/ECS.h"
#include "../EventSystem/EventBus.hpp"
#include "../InputManager/InputManager.h"
#include "../Components/CollectibleComponent.h"
#include "../Components/PlayerInventoryComponent.h"
#include "../EventSystem/Events/CollisionEvent.h"

class CollectibleSystem : public System {
public:
	void SubscribeToEvents(EventBus &eventBus, InputManager *_input) {
		eventBus.SubscribeToEvent<CollectibleSystem, CollisionEvent>(this, &CollectibleSystem::OnPlayerCast);
		input = _input;
	}

	void OnPlayerCast(CollisionEvent &e) {
		if(!input) return;
		if(!input->isKeyDown(KEY_E)) return;

		if(e.a.HasTag(PlayerInteractionCast) and e.b.HasTag(Collectible)
		or e.a.HasTag(Collectible) and e.b.HasTag(PlayerInteractionCast)) {

			Entity interaction = e.a.HasTag(PlayerInteractionCast) ? e.a : e.b;
			Entity collectible = e.a.HasTag(Collectible) ? e.a : e.b;

			auto &inventory = interaction.GetComponent<PlayerInventoryComponent>();
			const auto &collectComp = collectible.GetComponent<CollectibleComponent>();

			switch (collectComp.collId) {
			case Card:
				inventory.hasCard = true;
				collectible.Kill();
				break;
			case Key:
				inventory.hasKey = true;
				collectible.Kill();
				break;
			case Bomb:
				inventory.hasBomb = true;
				collectible.Kill();
				break;
			}
		}
	};

	InputManager *input = nullptr;
};
