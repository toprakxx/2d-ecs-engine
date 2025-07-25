#pragma once 
#include <SDL.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl2.h>
#include <imgui/imgui_impl_sdlrenderer2.h>
#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/AnimationComponent.h"
#include "../Components/RigidBodyComponent.h"

class ImGuiRenderSystem : public System {
public:
	ImGuiRenderSystem() = default;

	void Update(SDL_Renderer* renderer, SDL_Rect& camera, Registry& registry, double deltaTime) {
		ImGui_ImplSDLRenderer2_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();

		if(ImGui::Begin("Blue man teleporter")) {
			static float xPos;
			static float yPos;
			ImGui::InputFloat("x position", &xPos);
			ImGui::InputFloat("y position", &yPos);

			if(ImGui::Button("Teleport blue man")) {
				std::vector<Entity>* entities = registry.u_GetEntitiesWithTag(Tag::Player);
				if(entities) {
					for (auto entity : *entities) {
						auto& transform = entity.GetComponent<TransformComponent>();

						transform.position.x = xPos;
						transform.position.y = yPos;
					}
				}
			}

			static int xVel;
			static int yVel;
			ImGui::InputInt("x velocity", &xVel);
			ImGui::InputInt("y velocity", &yVel);

			if(ImGui::Button("Change velocity")) {
				std::vector<Entity>* entities = registry.u_GetEntitiesWithTag(Tag::Player);
				if(entities) {
					for (auto entity : *entities) {
						auto& rb = entity.GetComponent<RigidBodyComponent>();

						rb.velocity.x = xVel;
						rb.velocity.y = yVel;
					}
				}
			}

			static bool walkingLeft = false;
			if(ImGui::Button("Change animation direction")) {
				std::vector<Entity>* entities = registry.u_GetEntitiesWithTag(Tag::Player);
				if(entities) {
					for (auto entity : *entities) {
						auto& animation = entity.GetComponent<AnimationComponent>();
						animation.currentAnimation = walkingLeft ? animation.animations.at("WalkRight") : animation.animations.at("WalkLeft") ;
						walkingLeft = !walkingLeft;
					}
				}
			}
		}
		ImGui::End(); //Comment out for demo window

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
