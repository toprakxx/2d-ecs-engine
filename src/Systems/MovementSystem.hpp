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

			//This is a different version of the following: 
			//speed += accelaration * dt * 0.5
			//position += velocity * dt
			//speed += accelaratoin * dt * 0.5
			//This is the velocity-verlet (aka leapfrog)
			
			transformComponent.position.x += (rigidBodyComponent.velocity.x + deltaTime * rigidBodyComponent.acceleration.x / 2) * deltaTime;
			transformComponent.position.y += (rigidBodyComponent.velocity.y + deltaTime * rigidBodyComponent.acceleration.y / 2) * deltaTime;

			rigidBodyComponent.velocity.x += rigidBodyComponent.acceleration.x * deltaTime;
			rigidBodyComponent.velocity.y += rigidBodyComponent.acceleration.y * deltaTime;

		}
	}
};
