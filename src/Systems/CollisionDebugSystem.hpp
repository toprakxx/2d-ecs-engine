#pragma once
#include <SDL.h>
#include <glm/glm.hpp>
#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/BoxColliderComponent.h"

class CollisionDebugSystem : public System {
public:
	CollisionDebugSystem() {
		RequireComponent<TransformComponent>();
		RequireComponent<BoxColliderComponent>();
	}
	
	void Update(SDL_Renderer* renderer, bool inDebugMode, SDL_Rect& camera) {
		if(!inDebugMode) return;
		for (auto entity : GetSystemEntities()) {
			const auto& transform = entity.GetComponent<TransformComponent>();
			const auto& collider = entity.GetComponent<BoxColliderComponent>();

			SDL_Rect colliderRect = {
				static_cast<int>(transform.position.x + collider.offset.x - camera.x),
				static_cast<int>(transform.position.y + collider.offset.y - camera.y),
				static_cast<int>(collider.width),
				static_cast<int>(collider.height)
			};
			if (collider.inCollision) {
				SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			}
			else {
				SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
			}
			SDL_RenderDrawRect(renderer, &colliderRect);
		}
	}
};
