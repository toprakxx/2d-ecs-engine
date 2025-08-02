#pragma once
#include <SDL.h>
#include "../ECS/ECS.h"
#include "../Components/UIButtonComponent.h"
#include "../Components/TransformComponent.h"

class UIDebugSystem : public System {
public:
	UIDebugSystem() {
		RequireComponent<UIButtonComponent>();
		RequireComponent<TransformComponent>();
	}

	void Update(SDL_Renderer* renderer, SDL_Rect& camera) {
		for (auto& e : GetSystemEntities()) {
			const auto& transform = e.GetComponent<TransformComponent>();
			const auto& button = e.GetComponent<UIButtonComponent>();

			SDL_Rect colliderRect = {
				static_cast<int>(transform.position.x - camera.x),
				static_cast<int>(transform.position.y - camera.y),
				static_cast<int>(button.width),
				static_cast<int>(button.height)
			};
			if (button.mouseHover) {
				SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			}
			else {
				SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
			}
			SDL_RenderDrawRect(renderer, &colliderRect);
		}
	}
};
