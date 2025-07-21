#pragma once
#include <SDL.h>
#include "../ECS/ECS.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/TransformComponent.h"
#include "../EventSystem/EventBus.hpp"
#include "../EventSystem/Events/CollisionEvent.h"

class CollisionSystem : public System {
public:
	CollisionSystem() {
		RequireComponent<BoxColliderComponent>();
		RequireComponent<TransformComponent>();
	}

	void Update(EventBus& eventBus) {
		auto entities = GetSystemEntities();

		for (auto entity : entities) entity.GetComponent<BoxColliderComponent>().inCollision = false;

		for (auto i = entities.begin(); i != entities.end(); i++) { 
			Entity a = *i;
			auto aTransform = a.GetComponent<TransformComponent>();
			auto& aBoxCollider = a.GetComponent<BoxColliderComponent>();
			if(!aBoxCollider.isEnabled) continue;

			for (auto j = std::next(i); j != entities.end(); j++) {
				Entity b = *j;
				auto bTransform = b.GetComponent<TransformComponent>();
				auto& bBoxCollider = b.GetComponent<BoxColliderComponent>();
				if(!bBoxCollider.isEnabled) continue;

				bool collisionHappened = CheckAABBCollision(aTransform, aBoxCollider, bTransform, bBoxCollider);

				if (collisionHappened) {
					aBoxCollider.inCollision = true;
					bBoxCollider.inCollision = true;
					eventBus.EmitEvent<CollisionEvent>(a, b);
				}
			}
	   }
	}

	bool CheckAABBCollision(TransformComponent at, BoxColliderComponent ac,
						 	TransformComponent bt, BoxColliderComponent bc) {

		double ax = at.position.x + ac.offset.x;
		double ay = at.position.y + ac.offset.y;
		double bx = bt.position.x + bc.offset.x;
		double by = bt.position.y + bc.offset.y;

		return (
		ax < bx + bc.width &&
		ax + ac.width > bx &&
		ay < by + bc.height &&
		ay + ac.height > by
		);
	}
};
