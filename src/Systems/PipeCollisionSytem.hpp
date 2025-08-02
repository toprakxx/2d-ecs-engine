#pragma once 
#include "../ECS/ECS.h"
#include "../Systems/AnimationSystem.hpp"
#include "../Components/ColliderComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/PlayerControlComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../EventSystem/EventBus.hpp"
#include "../EventSystem/Events/CollisionEvent.h"
#include "glm/geometric.hpp"

class PipeCollisionSystem : public System {
public:
	void SubscribeToEvents(EventBus& eventBus) {
		eventBus.SubscribeToEvent<PipeCollisionSystem, CollisionEvent>(this, &PipeCollisionSystem::OnPipeCollision);
	}

	void OnPipeCollision(CollisionEvent& e) {
		if(e.a.HasTag(Player) and e.b.HasTag(Obstacle)
		or e.a.HasTag(Obstacle) and e.b.HasTag(Player)) {
			Entity player = (e.a.HasTag(Player)) ? e.a : e.b;
			Entity pipe = (e.b.HasTag(Obstacle)) ? e.b : e.a;

			auto& pT = player.GetComponent<TransformComponent>();
			auto& pC = player.GetComponent<ColliderComponent>();
			auto& pRB = player.GetComponent<RigidBodyComponent>();
			auto& pCC = player.GetComponent<PlayerControlComponent>();
			auto& pipeT = pipe.GetComponent<TransformComponent>();
			auto& pipeC = pipe.GetComponent<ColliderComponent>();

			glm::vec2 circleCenter = pT.position + pC.offset;
			glm::vec2 boxHalfExtends = glm::vec2(pipeC.width_2r/2.0, pipeC.height/2.0);
			glm::vec2 boxCenter = pipeT.position + pipeC.offset + boxHalfExtends;

			glm::vec2 difference = circleCenter - boxCenter;
			glm::vec2 clamped = glm::clamp(difference, -boxHalfExtends, boxHalfExtends);
			glm::vec2 closest = boxCenter + clamped;
			difference = circleCenter - closest;

			difference = glm::normalize(difference);

			pCC.isActive = false;
			ChangeAnimation(player, "Dead");
			pRB.velocity = difference * 400.0f;
		}
	}
};
