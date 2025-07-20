#pragma once
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

		for (auto i = entities.begin(); i != entities.end(); i++) { 
			Entity a = *i;
			auto aTransform = a.GetComponent<TransformComponent>();
			auto aBoxCollider = a.GetComponent<BoxColliderComponent>();

			if(!aBoxCollider.isEnabled) continue;

			for (auto j = i + 1; j != entities.end(); j++) {
				Entity b = *i;
				auto bTransform = b.GetComponent<TransformComponent>();
				auto bBoxCollider = b.GetComponent<BoxColliderComponent>();

				bool collisionHappened = CheckAABBCollision(aTransform, aBoxCollider, bTransform, bBoxCollider);

				if (collisionHappened) {
					eventBus.EmitEvent<CollisionEvent>(a, b);
					aBoxCollider.inCollision = true;
					bBoxCollider.inCollision = true;
				}
				else {
					aBoxCollider.inCollision = false;
					bBoxCollider.inCollision = false;
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
