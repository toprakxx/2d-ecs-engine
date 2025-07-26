#pragma once
#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"

class MovementSystem : public System {
public:
	MovementSystem() {
		RequireComponent<TransformComponent>();
		RequireComponent<RigidBodyComponent>();
	}

	void Update(double deltaTime) {
		for (auto entity : GetSystemEntities()) {
			TransformComponent& transformComponent = entity.GetComponent<TransformComponent>();
			RigidBodyComponent& rigidBodyComponent = entity.GetComponent<RigidBodyComponent>();

			//Mid-Point Integration
			transformComponent.position.x += (rigidBodyComponent.velocity.x + (rigidBodyComponent.acceleration.x/2 * deltaTime)) * deltaTime;
			transformComponent.position.y += (rigidBodyComponent.velocity.y + (rigidBodyComponent.acceleration.y/2 * deltaTime)) * deltaTime;

			rigidBodyComponent.velocity.x += rigidBodyComponent.acceleration.x * deltaTime;
			rigidBodyComponent.velocity.y += rigidBodyComponent.acceleration.y * deltaTime;

		}
	}
};
