#pragma once
#include <SDL.h>
#include <string>
#include <typeinfo>
#include "../ECS/ECS.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../EventSystem/EventBus.hpp"
#include "../EventSystem/Events/CollisionEvent.h"
#include "SDL_render.h"
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

				bool collisionHappened = CheckCollision(a,b);

				if (collisionHappened) {
					aCollider.inCollision = true;
					bCollider.inCollision = true;
					eventBus.EmitEvent<CollisionEvent>(a, b);
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
					glm::vec2 aCenter = at.position + (a.HasComponent<SpriteComponent>() ? glm::vec2(a.GetComponent<SpriteComponent>().width * at.scale.x / 2.0f) : glm::vec2(ac.w_r));
					glm::vec2 bCenter = bt.position + (b.HasComponent<SpriteComponent>() ? glm::vec2(b.GetComponent<SpriteComponent>().width * at.scale.x / 2.0f) : glm::vec2(ac.w_r));

					float r = ac.w_r + bc.w_r;
					r *= r;
					return r < (aCenter.x + bCenter.x)*(aCenter.x + bCenter.x) + 
					(aCenter.y + bCenter.y)*(aCenter.y + bCenter.y);
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

		glm::vec2 circleCenter = at.position + (a.HasComponent<SpriteComponent>()
			? glm::vec2((a.GetComponent<SpriteComponent>().width * at.scale.x) / 2.0f)
			: glm::vec2(ac.w_r)
		);
		glm::vec2 boxCenter = glm::vec2(bt.position.x + bc.w_r/2.0, bt.position.y + bc.h/2.0);
		glm::vec2 boxHalfExtends = glm::vec2(bc.w_r/2.0, bc.h/2.0);

		glm::vec2 difference = circleCenter - boxCenter;
		glm::vec2 clamped = glm::clamp(difference, -boxHalfExtends, boxHalfExtends);
		glm::vec2 closest = boxCenter + clamped;
		difference = closest - circleCenter;

		return glm::length(difference) < ac.w_r;
	}
};
