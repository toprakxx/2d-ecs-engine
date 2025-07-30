#pragma once 
#include <SDL.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl2.h>
#include <imgui/imgui_impl_sdlrenderer2.h>
#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/PlayerControlComponent.h"

class ImGuiRenderSystem : public System {
public:
	ImGuiRenderSystem() = default;

	void Update(SDL_Renderer* renderer, SDL_Rect& camera, Registry& registry, double deltaTime) {
		ImGui_ImplSDLRenderer2_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();

		// if(ImGui::Begin("Blue man teleporter")) {
		// 	static float xPos;
		// 	static float yPos;
		// 	ImGui::InputFloat("x position", &xPos);
		// 	ImGui::InputFloat("y position", &yPos);
		//
		// 	if(ImGui::Button("Teleport blue man")) {
		// 		std::vector<Entity>* entities = registry.u_GetEntitiesWithTag(Tag::Player);
		// 		if(entities) {
		// 			for (auto entity : *entities) {
		// 				auto& transform = entity.GetComponent<TransformComponent>();
		//
		// 				transform.position.x = xPos;
		// 				transform.position.y = yPos;
		// 			}
		// 		}
		// 	}
		//
		// 	static int playerSpeed;
		// 	ImGui::InputInt("Player speed", &playerSpeed);
		//
		// 	if(ImGui::Button("Change speed")) {
		// 		std::vector<Entity>* entities = registry.u_GetEntitiesWithTag(Tag::Player);
		// 		if(entities) {
		// 			for (auto entity : *entities) {
		// 				auto& pControl = entity.GetComponent<PlayerControlComponent>();
		//
		// 				pControl.playerSpeed = playerSpeed;
		// 			}
		// 		}
		// 	}
		// }
		// ImGui::End(); //Comment out for demo window

		// Display a small overlay window to display the map position using the mouse
		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoNav;
		ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always, ImVec2(0, 0));
		ImGui::SetNextWindowBgAlpha(0.9f);
		if (ImGui::Begin("Map coordinates", NULL, windowFlags)) {
			ImGui::Text(
				"Mouse map coordinates (x=%.1f, y=%.1f)",
				ImGui::GetIO().MousePos.x + camera.x,
				ImGui::GetIO().MousePos.y + camera.y
			);
			ImGui::Text(
				"FPS: %.1f", ImGui::GetIO().Framerate);
		}
		ImGui::End();

		// ImGui::ShowDemoWindow();

		ImGui::Render();
		ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);
	}
};
