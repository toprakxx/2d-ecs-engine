#pragma once
#include <iostream>
#include <ostream>
#include "../ECS/ECS.h"
#include "../SceneLoader/SceneLoader.h"
#include "../Systems/AnimationSystem.hpp"
#include "../Components/ColliderComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/PlayerControlComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../EventSystem/EventBus.hpp"
#include "../EventSystem/Events/CollisionEvent.h"
#include "../EventSystem/Events/SoundEffectEvent.h"

class ObstacleCollisionSystem : public System {
public:
	void SubscribeToEvents(EventBus &eventBus){
		eventBus.SubscribeToEvent<ObstacleCollisionSystem, CollisionEvent>(this, &ObstacleCollisionSystem::OnObstacleCollision);
	}

	void OnObstacleCollision(CollisionEvent &e) {
		if(e.a.HasTag(Player) and e.b.HasTag(Obstacle)
		or e.a.HasTag(Obstacle) and e.b.HasTag(Player)) {

			Entity player = e.a.HasTag(Player) ? e.a : e.b;
			Entity wall = e.a.HasTag(Obstacle) ? e.a : e.b;

			auto& pT  = player.GetComponent<TransformComponent>();
			auto& pC  = player.GetComponent<ColliderComponent>();
			auto& pRB = player.GetComponent<RigidBodyComponent>();

			auto& wT = wall.GetComponent<TransformComponent>();
			auto& wC = wall.GetComponent<ColliderComponent>();

			// Centers and half-extents
			glm::vec2 pHalf = { pC.width_2r * 0.5f,  pC.height * 0.5f };
			glm::vec2 wHalf = { wC.width_2r * 0.5f,  wC.height * 0.5f };

			glm::vec2 pCenter = pT.position + pC.offset + pHalf;
			glm::vec2 wCenter = wT.position + wC.offset + wHalf;

			// Overlap on each axis
			float dx = wCenter.x - pCenter.x;
			float px = (wHalf.x + pHalf.x) - std::fabs(dx);

			float dy = wCenter.y - pCenter.y;
			float py = (wHalf.y + pHalf.y) - std::fabs(dy);

			if (px <= 0.f || py <= 0.f) return; // no overlap (guard)

			// Resolve on the shallow axis; stop velocity on that axis
			if (px < py) {
				float corr = (dx > 0.f) ? -px : px;      // push player out on X
				pT.position.x += corr;
				pRB.velocity.x = 0.f;
			} else {
				float corr = (dy > 0.f) ? -py : py;      // push player out on Y
				pT.position.y += corr;
				pRB.velocity.y = 0.f;
			}

		}
	}
};
