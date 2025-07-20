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

			rigidBodyComponent.velocity.x += rigidBodyComponent.acceleration.x * deltaTime;
			rigidBodyComponent.velocity.y += rigidBodyComponent.acceleration.y * deltaTime;

			transformComponent.position.x += rigidBodyComponent.velocity.x * deltaTime;
			transformComponent.position.y += rigidBodyComponent.velocity.y * deltaTime;
		}
	}
	
};
