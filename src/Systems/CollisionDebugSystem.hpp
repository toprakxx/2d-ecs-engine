#pragma once
#include <array>
#include <cmath>
#include <SDL.h>
#include <glm/glm.hpp>
#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/SpriteComponent.h"

class CollisionDebugSystem : public System {
public:
	CollisionDebugSystem() {
		RequireComponent<TransformComponent>();
		RequireComponent<ColliderComponent>();
	}
	
	void Update(SDL_Renderer* renderer, SDL_Rect& camera) {
		for (auto entity : GetSystemEntities()) {
			const auto& transform = entity.GetComponent<TransformComponent>();
			const auto& collider = entity.GetComponent<ColliderComponent>();

			if(collider.type == Circle) {
				glm::vec2 centerOffset = glm::vec2(collider.w_r);

				if(entity.HasComponent<SpriteComponent>()) {
					const auto sprite = entity.GetComponent<SpriteComponent>();
					centerOffset = glm::vec2((sprite.width * transform.scale.x)/2.0);
				}

				int centerX = (
					transform.position.x
					+ centerOffset.x
					+ collider.offset.x
					- camera.x
				);
				int centerY = (
					transform.position.y
					+ centerOffset.y
					+ collider.offset.y
					- camera.y
				);
				int r = collider.w_r;

				//Segment number for the circle
				const int N = 32;
				const float angleStep = 2.0f;
				std::array<SDL_Point, N+1> points;

				for (int i = 0; i <= N; i++){
					float pAngle = (angleStep * float(M_PI) * i) / N;
					points[i] = {
						centerX + int(std::cos(pAngle) * r),
						centerY + int(std::sin(pAngle) * r)
					};
				}

				if (collider.inCollision) {
					SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
				}
				else {
					SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
				}
				SDL_RenderDrawLines(renderer, points.data(), N+1);

				continue;
			}

			SDL_Rect colliderRect = {
				static_cast<int>(transform.position.x + collider.offset.x - camera.x),
				static_cast<int>(transform.position.y + collider.offset.y - camera.y),
				static_cast<int>(collider.w_r),
				static_cast<int>(collider.h)
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
