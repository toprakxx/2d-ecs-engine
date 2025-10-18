#pragma once
#include <SDL.h>
#include "../ECS/ECS.h"
#include "../Components/PlayerControlComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/ParentComponent.h"

class PlayerInteractionSystem : public System {
public:
	PlayerInteractionSystem() {
		RequireComponent<TransformComponent>();
		RequireComponent<ParentComponent>();
		RequireComponent<PlayerControlComponent>();
	}

	void Update() {
		for (auto &e : GetSystemEntities()) {
			if (!e.HasTag(Player)) return;
			auto &playerParentComp = e.GetComponent<ParentComponent>();
			auto & playerController = e.GetComponent<PlayerControlComponent>();
			auto it = std::find_if(playerParentComp.children.begin(), playerParentComp.children.end(), [](Child c){
				return c.entity.HasTag(PlayerInteractionCast);
			});
			if (it == playerParentComp.children.end()) return;

			glm::vec2& off = it->offset;
			const float S  = SCALE_FACTOR_32;
			const float PW = 32.0f * S; // player sprite width (px)
			const float PH = 32.0f * S; // player sprite height (px)
			const float CW = float(PLAYER_INTERACTION_WIDTH);
			const float CH = float(PLAYER_INTERACTION_HEIGHT);
			const float M  = 5.0f;      // small margin

			switch (playerController.state) {
				case IDLE_SOUTH: case WALK_SOUTH:
					off.x = ((PW - CW) * 0.5f);
					off.y = PH + M;
					break;

				case IDLE_NORTH: case WALK_NORTH:
					off.x = ((PW - CW) * 0.5f);
					off.y = - CH - M;
					break;

				case IDLE_EAST: case WALK_EAST:
					off.x = PW + M;
					off.y = (PH - CH) * 0.5f;
					break;

				case IDLE_WEST: case WALK_WEST:
					off.x = -CW - M;
					off.y = (PH - CH) * 0.5f;
					break;

				default: break;
			}
		}
	}
};
