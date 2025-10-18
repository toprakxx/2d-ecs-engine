#pragma once
#include "../ECS/ECS.h"
#include "../Components/ParentComponent.h"
#include "../Components/TransformComponent.h"
#include "glm/fwd.hpp"

class ParentSystem : public System {
public:
	ParentSystem() {
		RequireComponent<TransformComponent>();
		RequireComponent<ParentComponent>();
	}

	void Update() {
		for (auto e : GetSystemEntities()) {
			TransformComponent &parentTransform = e.GetComponent<TransformComponent>();
			ParentComponent	 &parentComponent = e.GetComponent<ParentComponent>();

			for (int i = 0; i < parentComponent.childCount; i++) {
				Child &child = parentComponent.children[i];
				child.entity.GetComponent<TransformComponent>().position =
					parentTransform.position + child.offset;
			}
		}
	}
};
