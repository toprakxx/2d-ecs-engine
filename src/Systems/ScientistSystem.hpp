#pragma once
#include "../ECS/ECS.h"
#include "../EventSystem/EventBus.hpp"
#include "../InputManager/InputManager.h"
#include "../Components/PasswordManagerComponent.h"
#include "../Components/ScientistComponent.h"
#include "../EventSystem/Events/CollisionEvent.h"
#include "../EventSystem/Events/SoundEffectEvent.h"

class ScientistSystem : public System {
public:
	void SubscribeToEvents(EventBus &eventBust, InputManager *_input, Registry *_registry) {
		eventBust.SubscribeToEvent(this, &ScientistSystem::OnPlayerCast);
		input = _input;
		registry = _registry;
		eb = &eventBust;
	}

	void OnPlayerCast(CollisionEvent &e){
		if(!input) return;
		if(!input->isKeyDown(KEY_E)) return;

		if(e.a.HasTag(PlayerInteractionCast) and e.b.HasTag(Scientist)
		or e.a.HasTag(Scientist) and e.b.HasTag(PlayerInteractionCast)) {

			Entity scientist = e.a.HasTag(Scientist) ? e.a : e.b;
			auto &sciComp = scientist.GetComponent<ScientistComponent>();
			if (sciComp.beenRead) return;
			auto entities = registry->u_GetEntitiesWithTag(PasswordManager);
			for (auto &e : *entities) {
				e.GetComponent<PasswordManagerComponent>().numKnownDigits++;
				eb->EmitEvent<SoundEffectEvent>("password-sfx");
				sciComp.beenRead = true;
			}
		}
	}

	InputManager *input = nullptr;
	Registry *registry = nullptr;
	EventBus *eb = nullptr;
};
