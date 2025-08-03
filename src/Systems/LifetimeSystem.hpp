#pragma once
#include "../ECS/ECS.h"
#include "../Components/LifetimeComponent.h"

class LifetimeSystem : public System {
public:
	LifetimeSystem() {
		RequireComponent<LifetimeComponent>();
	}

	void Update(double deltaTime) {
		for (auto& e : GetSystemEntities()) {
			auto& life = e.GetComponent<LifetimeComponent>();

			life.time -= deltaTime;
			if(life.time <= 0) e.Kill();
		}
	}
};
