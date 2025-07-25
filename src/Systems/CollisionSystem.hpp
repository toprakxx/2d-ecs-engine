#pragma once
#include <SDL.h>
#include <typeinfo>
#include "../ECS/ECS.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/TransformComponent.h"
#include "../EventSystem/EventBus.hpp"
#include "../EventSystem/Events/CollisionEvent.h"
#include "glm/fwd.hpp"

class CollisionSystem : public System {
public:
	CollisionSystem() {
		RequireComponent<ColliderComponent>();
		RequireComponent<TransformComponent>();
	}

	void Update(EventBus& eventBus) {
		auto entities = GetSystemEntities();

		for (auto entity : entities) entity.GetComponent<ColliderComponent>().inCollision = false;

		for (auto i = entities.begin(); i != entities.end(); i++) { 
			Entity a = *i;
			auto aTransform = a.GetComponent<TransformComponent>();
			auto& aCollider = a.GetComponent<ColliderComponent>();
			if(!aCollider.isEnabled) continue;

			for (auto j = std::next(i); j != entities.end(); j++) {
				Entity b = *j;
				auto bTransform = b.GetComponent<TransformComponent>();
				auto& bCollider = b.GetComponent<ColliderComponent>();
				if(!bCollider.isEnabled) continue;

				bool collisionHappened = CheckCollision(aTransform, aCollider, bTransform, bCollider);

				if (collisionHappened) {
					aCollider.inCollision = true;
					bCollider.inCollision = true;
					eventBus.EmitEvent<CollisionEvent>(a, b);
				}
			}
	   }
	}

	bool CheckCollision(TransformComponent at, ColliderComponent ac,
						TransformComponent bt, ColliderComponent bc) {
		Collider aType = ac.type;
		Collider bType = bc.type;

		switch(aType) {
			case Collider::Box: {
				if(bType == Box) {
					//X-axis collision
					bool collisionX = at.position.x + ac.width >= bt.position.x &&
						bt.position.x + bc.width >= at.position.x;
					//Y-axis collision
					bool collisionY = at.position.y + ac.height >= bt.position.y &&
						bt.position.y + bc.height >= at.position.y;

					return collisionX && collisionY;
				} 
				//b is Circle
				return CircleAndBoxCollision(bt, bc, at, ac);
			} break;

			case Collider::Circle: {
				if(bType == Circle) {
					glm::vec2 aCenter = at.position + glm::vec2(ac.width/2.0);
					glm::vec2 bCenter = bt.position + glm::vec2(bc.width/2.0);

					float r = ac.width + bc.width;
					r *= r;
					return r < (aCenter.x + bCenter.x)*(aCenter.x + bCenter.x) + 
					(aCenter.y + bCenter.y)*(aCenter.y + bCenter.y);
				}
				//a is Circle
				return CircleAndBoxCollision(at, ac, bt, bc);
			} break;

			default: Logger::Err("Erronous trigger of the collision system");
			return false;
		}
	}

	//https://learnopengl.com/In-Practice/2D-Game/Collisions/Collision-detection
	bool CircleAndBoxCollision(TransformComponent at, ColliderComponent ac,
							TransformComponent bt, ColliderComponent bc) {
		glm::vec2 circleCenter = at.position + glm::vec2(ac.width/2.0);
		glm::vec2 boxCenter = glm::vec2(bt.position.x + bc.width/2.0, bt.position.y + bc.height/2.0);
		glm::vec2 boxHalfExtends = glm::vec2(bc.width/2.0, bc.height/2.0);

		glm::vec2 difference = circleCenter - boxCenter;
		glm::vec2 clamped = glm::clamp(difference, -boxHalfExtends, boxHalfExtends);
		glm::vec2 closest = boxCenter + clamped;
		difference = closest - circleCenter;

		return glm::length(difference) < bc.width;
	}
};
