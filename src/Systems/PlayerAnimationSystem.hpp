#pragma once
#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/AnimationComponent.h"
#include "../Components/PlayerControlComponent.h"
#include "../Systems/AnimationSystem.hpp"

class PlayerAnimationSystem : public System {
public:
	PlayerAnimationSystem() {
		RequireComponent<TransformComponent>();
		RequireComponent<AnimationComponent>();
		RequireComponent<PlayerControlComponent>();
	};

	void Update() {
		for (auto &e : GetSystemEntities()) {
			auto &playerController = e.GetComponent<PlayerControlComponent>();

			switch (playerController.state) {
				case IDLE_SOUTH: ChangeAnimation(e, "IdleSouth"); break;
				case IDLE_EAST: ChangeAnimation(e, "IdleEast"); break;
				case IDLE_NORTH: ChangeAnimation(e, "IdleNorth"); break;
				case IDLE_WEST: ChangeAnimation(e, "IdleWest"); break;
				case WALK_SOUTH: ChangeAnimation(e, "WalkSouth"); break;
				case WALK_EAST: ChangeAnimation(e, "WalkEast"); break;
				case WALK_NORTH: ChangeAnimation(e, "WalkNorth"); break;
				case WALK_WEST: ChangeAnimation(e, "WalkWest"); break;
			}
		}
	}
};
