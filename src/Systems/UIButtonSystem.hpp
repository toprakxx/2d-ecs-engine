#pragma once
#include <SDL.h>
#include <imgui/imgui.h>
#include "../ECS/ECS.h"
#include "../InputManager/InputManager.h"
#include "../Components/UIButtonComponent.h"
#include "../Components/TransformComponent.h"
#include "../EventSystem/EventBus.hpp"
#include "../EventSystem/Events/ButtonClickEvent.h"

class UIButtonSystem : public System {
public:
	UIButtonSystem() {
		RequireComponent<UIButtonComponent>();
		RequireComponent<TransformComponent>();
	}

	void Update(EventBus& eventBus, const SDL_Rect& camera, const InputManager& input) {
		for (auto e : GetSystemEntities()) {
			auto& button = e.GetComponent<UIButtonComponent>();
			const auto& transform = e.GetComponent<TransformComponent>();

			glm::vec2 mousePos = input.GetMousePosition();
			int mouseX = mousePos.x + camera.x;
			int mouseY = mousePos.y + camera.y;
			bool mouseHover = mouseX > transform.position.x + button.offset.x
				and mouseX < transform.position.x + button.width + button.offset.x
				and mouseY > transform.position.y + button.offset.y
				and mouseY < transform.position.y + button.height + button.offset.y;
			button.mouseHover = mouseHover;

			if(mouseHover and input.isMousePressed(MOUSE_L)) {
				if(button.callback) button.callback();
				eventBus.EmitEvent<ButtonClickedEvent>(e);
			}
		}
	}
};
