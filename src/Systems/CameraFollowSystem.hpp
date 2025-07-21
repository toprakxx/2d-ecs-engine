#pragma once
#include <SDL.h>
#include "../ECS/ECS.h"
#include "../Components/CameraFollowComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"

class CameraFollowSystem : public System {
public:
	CameraFollowSystem() {
		RequireComponent<CameraFollowComponent>();
		RequireComponent<TransformComponent>();
	}

	void Update(SDL_Rect& camera) {
		for (auto entity : GetSystemEntities()) {
			auto transform = entity.GetComponent<TransformComponent>();

			SpriteComponent sprite;
			bool hasSprite = entity.HasComponent<SpriteComponent>();
			if (hasSprite) {
				sprite = entity.GetComponent<SpriteComponent>();
			}

			camera.x = transform.position.x - (camera.w/2.0f) 
				+ (hasSprite ? (sprite.width/2.0f) * transform.scale.x : 0);
			camera.y = transform.position.y - (camera.h/2.0f)
				+ (hasSprite ? (sprite.height/2.0f) * transform.scale.y : 0);
		}
	}
};
