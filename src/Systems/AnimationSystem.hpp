#pragma once
#include "../ECS/ECS.h"
#include "../Components/AnimationComponent.h"
#include "../Components/SpriteComponent.h"

class AnimationSystem : public System {
public:
	AnimationSystem() {
		RequireComponent<AnimationComponent>();
		RequireComponent<SpriteComponent>();
	}

	void Update(double deltaTime) {
		for (auto entity : GetSystemEntities()) {
			auto& sprite = entity.GetComponent<SpriteComponent>();
			AnimationComponent& animationComponent = entity.GetComponent<AnimationComponent>();
			auto& animation = animationComponent.currentAnimation;

			animation.frameTimer -= deltaTime;
			if(animation.frameTimer <= 0) {
				animation.currentFrame = (animation.currentFrame + 1 ) % animation.animationFrameCount;
				sprite.srcRect.x = sprite.width * animation.currentFrame;
				sprite.srcRect.y = sprite.height * animation.sheetIndex;
				animation.frameTimer = animation.secondsPerAnimationFrame;
			}
		}
	}
};
