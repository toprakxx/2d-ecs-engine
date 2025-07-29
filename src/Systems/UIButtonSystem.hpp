#pragma once
#include <imgui/imgui.h>
#include "../ECS/ECS.h"
#include "../Components/UIButtonComponent.h"
#include "../Components/TransformComponent.h"
#include "../EventSystem/EventBus.hpp"
#include "../EventSystem/Events/ButtonClickEvent.h"

class UIButtonSystem : public System {
	UIButtonSystem() {
		RequireComponent<UIButtonComponent>();
		RequireComponent<TransformComponent>();
	}

	void Update(EventBus& eventBus) {
		for (auto e : GetSystemEntities()) {
			const auto& button = e.GetComponent<UIButtonComponent>();
			const auto& transform = e.GetComponent<TransformComponent>();

			int mouseX = ImGui::GetIO().MousePos.x;
			int mouseY = ImGui::GetIO().MousePos.y;

			if (mouseX > transform.position.x and mouseX < transform.position.x + button.width and
				mouseY > transform.position.y and mouseY < transform.position.y + button.height ) {
				eventBus.EmitEvent<ButtonClickedEvent>(e);
			}
		}
	}
};
