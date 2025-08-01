#pragma once
#include <algorithm>
#include <utility>
#include <unordered_set>
#include <SDL.h>
#include "../ECS/ECS.h"
#include "../Components/ColliderComponent.h"
#include "../Components/TransformComponent.h"
#include "../EventSystem/EventBus.hpp"
#include "../EventSystem/Events/CollisionEvent.h"
#include "../EventSystem/Events/CollisionEnterEvent.h"
#include "../EventSystem/Events/CollisionExitEvent.h"

//NOTE: Change circle collider from taking in the radius to taking in the diameter to simplify this and the debug system
//NOTE: Find a way to clean the collison map when a entity dies (from the entries of that entity)

class CollisionSystem : public System {
public:
	CollisionSystem() {
		RequireComponent<ColliderComponent>();
		RequireComponent<TransformComponent>();
		collidingPairs.reserve(VECTOR_INIT);
	}

	//For box colliders position of the entity + collider offset is the upper left corner
	//For circle colliders position of the entity + collider offset is the middle of the circle

	//https://leanrada.com/notes/sweep-and-prune
	//https://leanrada.com/notes/sweep-and-prune-2
	void Update(EventBus& eventBus) {
		std::vector<Entity>& entities = GetSystemEntities();
		for (auto entity : entities) entity.GetComponent<ColliderComponent>().inCollision = false;

		std::sort(entities.begin(), entities.end(), [](Entity& a, Entity& b) {
			const auto& aTrns = a.GetComponent<TransformComponent>();
			const auto& aColl = a.GetComponent<ColliderComponent>();
			const auto& bTrns = b.GetComponent<TransformComponent>();
			const auto& bColl = b.GetComponent<ColliderComponent>();

			auto aLeft = aTrns.position.x + aColl.offset.x;
			if (aColl.type == Circle) aLeft -= aColl.width_2r/2.0;
			auto bLeft = bTrns.position.x + bColl.offset.x;
			if (bColl.type == Circle) bLeft -= bColl.width_2r/2.0;

			return aLeft < bLeft;
		});
		
		for (auto i = entities.begin(); i != entities.end(); i++) { 
			Entity a = *i;
			auto aTrns = a.GetComponent<TransformComponent>();
			auto& aColl = a.GetComponent<ColliderComponent>();

			for (auto j = std::next(i); j != entities.end(); j++) {
				Entity b = *j;
				auto bTrns = b.GetComponent<TransformComponent>();
				auto& bColl = b.GetComponent<ColliderComponent>();

				auto bLeft = bTrns.position.x + bColl.offset.x;
				if (bColl.type == Circle) bLeft -= bColl.width_2r/2.0;
				auto aRight = aTrns.position.x + aColl.offset.x;
				if (aColl.type == Circle) aRight += aColl.width_2r/2.0;
				else aRight += aColl.width_2r;

				if (bLeft > aRight) break;

				bool collisionHappened = CheckCollision(a,b);

				if (collisionHappened) {
					aColl.inCollision = true;
					bColl.inCollision = true;
					auto temp = MakeEntityPair(a, b);
					if(!collidingPairs.contains(temp)) {
						Logger::Log("Collision enter between: " + std::to_string(a.id) + ", " + std::to_string(b.id));
						collidingPairs.insert(temp);
						eventBus.EmitEvent<CollisionEnterEvent>(a,b);
					}
					// Logger::Log("Collision between: " + std::to_string(a.id) + ", " + std::to_string(b.id));
					eventBus.EmitEvent<CollisionEvent>(a, b);
				}
			}
		}
		//Initial collision checks complete
		
		for (auto it = collidingPairs.begin(); it != collidingPairs.end();){
			if(CheckCollision(it->first, it->second)) {++it;}
			else {
				Logger::Log("Collision exit between: " + std::to_string(it->first.id) + ", " + std::to_string(it->second.id));
				eventBus.EmitEvent<CollisionExitEvent>(it->first, it->second);
				it = collidingPairs.erase(it);
			}
		}
	}

	bool CheckCollision(const Entity& a, const Entity& b) {
		const TransformComponent& aTrns = a.GetComponent<TransformComponent>();
		const ColliderComponent& aColl = a.GetComponent<ColliderComponent>();
		const TransformComponent& bTrns = b.GetComponent<TransformComponent>();
		const ColliderComponent& bColl = b.GetComponent<ColliderComponent>();

		Collider aType = aColl.type;
		Collider bType = bColl.type;

		switch(aType) {
			//AABB Collision
			case Collider::Box: {
				if(bType == Box) {
					double aX = aTrns.position.x + aColl.offset.x;
					double aY = aTrns.position.y + aColl.offset.y;
					double bX = bTrns.position.x + bColl.offset.x;
					double bY = bTrns.position.y + bColl.offset.y;

					return (
						aX < bX + bColl.width_2r and
						aX + aColl.width_2r > bX and
						aY < bY + bColl.height and
						aY + aColl.height > bY
					);
				} 
				//b is Circle
				return CircleAndBoxCollision(b,a);
			} break;

			//Circle-Circle Collsion
			case Collider::Circle: {
				if(bType == Circle) {
					glm::vec2 aCenter = aTrns.position + aColl.offset;
					glm::vec2 bCenter = bTrns.position + bColl.offset;
					float combinedR = (aColl.width_2r + bColl.width_2r)/2.0;

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
	bool CircleAndBoxCollision(const Entity& a, const Entity& b) {
		TransformComponent& aTrns = a.GetComponent<TransformComponent>();
		ColliderComponent& aColl = a.GetComponent<ColliderComponent>();
		TransformComponent& bTrns = b.GetComponent<TransformComponent>();
		ColliderComponent& bColl = b.GetComponent<ColliderComponent>();

		glm::vec2 circleCenter = aTrns.position + aColl.offset;
		glm::vec2 boxCenter = bTrns.position + bColl.offset + 
			glm::vec2(bColl.width_2r/2.0, bColl.height/2.0);
		glm::vec2 boxHalfExtends = glm::vec2(bColl.width_2r/2.0, bColl.height/2.0);

		glm::vec2 difference = circleCenter - boxCenter;
		glm::vec2 clamped = glm::clamp(difference, -boxHalfExtends, boxHalfExtends);
		glm::vec2 closest = boxCenter + clamped;
		difference = closest - circleCenter;

		return glm::length(difference) < aColl.width_2r/2.0;
	}

	std::pair<Entity,Entity> MakeEntityPair(Entity a, Entity b) {
		if(a.id < b.id) return {a,b};
		return {b,a};
	}

	struct EntityPairHash {
		std::size_t operator()(const std::pair<Entity,Entity>& p) const noexcept {
			return std::hash<int>{}(p.first.id) ^ (std::hash<int>{}(p.second.id) + 0x9e3779b9 + (std::hash<int>{}(p.first.id) << 6) + (std::hash<int>{}(p.first.id) >> 2));
		}
	};

	struct EntityPairEq {
		bool operator()(const std::pair<Entity,Entity>& a,
				  const std::pair<Entity,Entity>& b) const noexcept {
			return a.first.id == b.first.id && a.second.id == b.second.id;
		}
	};

private:
	std::unordered_set<std::pair<Entity, Entity>, EntityPairHash, EntityPairEq> collidingPairs;
};
