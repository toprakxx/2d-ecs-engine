#pragma once
#include <algorithm>
#include <SDL.h>
#include "../ECS/ECS.h"
#include "../Components/ColliderComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../EventSystem/EventBus.hpp"
#include "../EventSystem/Events/CollisionEvent.h"
#include "glm/geometric.hpp"

//NOTE: Add a "TriggerBox" system to compansate for making SpriteComponent mandatory for this system.
//NOTE: Collision offset is lacking consideration durint SAP
//NOTE: Change circle collider from taking in the radius to taking in the diameter to simplify this and the debug system
//NOTE: This whole code could really use a clean up to reduce repetitin and such

class CollisionSystem : public System {
public:
	CollisionSystem() {
		RequireComponent<ColliderComponent>();
		RequireComponent<TransformComponent>();
		RequireComponent<SpriteComponent>();
	}

	//https://leanrada.com/notes/sweep-and-prune
	//https://leanrada.com/notes/sweep-and-prune-2
	void Update(EventBus& eventBus) {
		std::vector<Entity>& entities = GetSystemEntities();
		for (auto entity : entities) entity.GetComponent<ColliderComponent>().inCollision = false;

		std::sort(entities.begin(), entities.end(), [](Entity a, Entity b) {
			const auto& at = a.GetComponent<TransformComponent>();
			const auto& ac = a.GetComponent<ColliderComponent>();
			const auto& as = a.GetComponent<SpriteComponent>();
			const auto& bt = b.GetComponent<TransformComponent>();
			const auto& bc = b.GetComponent<ColliderComponent>();
			const auto& bs = b.GetComponent<SpriteComponent>();

			auto aLeft = (ac.type == Collider::Circle)
				? at.position.x + (as.width/2.0 * at.scale.x) - ac.w_r
				: at.position.x + (as.width/2.0 * at.scale.x) - (ac.w_r/2.0);

			auto bLeft = (bc.type == Collider::Circle)
				? bt.position.x + (bs.width/2.0 * bt.scale.x) - bc.w_r
				: bt.position.x + (bs.width/2.0 * bt.scale.x) - (bc.w_r/2.0);

			return aLeft < bLeft;
		});
		
		for (auto i = entities.begin(); i != entities.end(); i++) { 
			Entity a = *i;
			auto at = a.GetComponent<TransformComponent>();
			auto& ac = a.GetComponent<ColliderComponent>();
			const auto& as = a.GetComponent<SpriteComponent>();

			for (auto j = std::next(i); j != entities.end(); j++) {
				Entity b = *j;
				auto bt = b.GetComponent<TransformComponent>();
				auto& bc = b.GetComponent<ColliderComponent>();
				const auto& bs = b.GetComponent<SpriteComponent>();

				auto aRight = (ac.type == Collider::Circle)
					? at.position.x + (as.width/2.0 * at.scale.x) + ac.w_r
					: at.position.x + (as.width/2.0 * at.scale.x) + (ac.w_r/2.0);

				auto bLeft = (bc.type == Collider::Circle)
					? bt.position.x + (bs.width/2.0 * bt.scale.x) - bc.w_r
					: bt.position.x + (bs.width/2.0 * bt.scale.x) - (bc.w_r/2.0);

				if (bLeft > aRight) break;

				bool collisionHappened = CheckCollision(a,b);

				if (collisionHappened) {
					ac.inCollision = true;
					bc.inCollision = true;
					eventBus.EmitEvent<CollisionEvent>(a, b);
					// Logger::Log("Collision between: " + std::to_string(a.id) + ", " + std::to_string(b.id));
				}
			}
		}
	}

	bool CheckCollision(Entity& a, Entity& b) {
		TransformComponent at = a.GetComponent<TransformComponent>();
		ColliderComponent ac = a.GetComponent<ColliderComponent>();
		TransformComponent bt = b.GetComponent<TransformComponent>();
		ColliderComponent bc = b.GetComponent<ColliderComponent>();

		Collider aType = ac.type;
		Collider bType = bc.type;

		switch(aType) {
			case Collider::Box: {
				if(bType == Box) {
					//X-axis collision
					bool collisionX = at.position.x + ac.w_r >= bt.position.x &&
						bt.position.x + bc.w_r >= at.position.x;
					//Y-axis collision
					bool collisionY = at.position.y + ac.h >= bt.position.y &&
						bt.position.y + bc.h >= at.position.y;

					return collisionX && collisionY;
				} 
				//b is Circle
				return CircleAndBoxCollision(b,a);
			} break;

			case Collider::Circle: {
				if(bType == Circle) {
					glm::vec2 aCenter = at.position + glm::vec2(a.GetComponent<SpriteComponent>().width * at.scale.x / 2.0f);
					glm::vec2 bCenter = bt.position + glm::vec2(b.GetComponent<SpriteComponent>().width * bt.scale.x / 2.0f);

					float combinedR = ac.w_r + bc.w_r;

					return glm::distance(aCenter, bCenter) < combinedR;
				}
				//a is Circle
				return CircleAndBoxCollision(a,b);
			} break;

			default: Logger::Err("Erronous trigger of the collision system");
			return false;
		}
	}

	//https://learnopengl.com/In-Practice/2D-Game/Collisions/Collision-detection
	bool CircleAndBoxCollision(Entity& a, Entity& b) {
		TransformComponent& at = a.GetComponent<TransformComponent>();
		ColliderComponent& ac = a.GetComponent<ColliderComponent>();
		TransformComponent& bt = b.GetComponent<TransformComponent>();
		ColliderComponent& bc = b.GetComponent<ColliderComponent>();

		glm::vec2 circleCenter = at.position + glm::vec2((a.GetComponent<SpriteComponent>().width * at.scale.x) / 2.0f);
		glm::vec2 boxCenter = glm::vec2(bt.position.x + bc.w_r/2.0, bt.position.y + bc.h/2.0);
		glm::vec2 boxHalfExtends = glm::vec2(bc.w_r/2.0, bc.h/2.0);

		glm::vec2 difference = circleCenter - boxCenter;
		glm::vec2 clamped = glm::clamp(difference, -boxHalfExtends, boxHalfExtends);
		glm::vec2 closest = boxCenter + clamped;
		difference = closest - circleCenter;

		return glm::length(difference) < ac.w_r;
	}
};
