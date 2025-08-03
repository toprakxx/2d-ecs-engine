#pragma once
#include "../ECS/ECS.h"
#include "../Components/ColliderComponent.h"
#include "../EventSystem/EventBus.hpp"
#include "../EventSystem/Events/CollisionEvent.h"

class DamageSystem : public System {
public:
	DamageSystem() {
		RequireComponent<ColliderComponent>();
	}

	void SubscribeToEvents(EventBus& eventBus) {
		eventBus.SubscribeToEvent<DamageSystem, CollisionEvent>(this, &DamageSystem::OnCollision);
	}
	
	void OnCollision(CollisionEvent& event) {
		// Logger::Log("Collission detected by the damage system.");

		if(event.a.HasTag(Death)) {
			auto& victim = (event.a.HasTag(Death)) ? event.b : event.a;
			victim.Kill();
		}
	}
};
