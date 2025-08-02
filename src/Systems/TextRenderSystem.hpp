#pragma once 
#include <SDL.h>
#include "../ECS/ECS.h"
#include "../AssetManager/AssetManager.h"
#include "../Components/TextComponent.h"
#include "../Components/TransformComponent.h"

class TextRenderSystem : public System {
public:
	TextRenderSystem() {
		RequireComponent<TextComponent>();
		RequireComponent<TransformComponent>();
	}

	void Update(SDL_Renderer* renderer, AssetManager& assetManager, const SDL_Rect& camera) {
		for (auto entity : GetSystemEntities()) {
			const auto& text = entity.GetComponent<TextComponent>();
			const auto& transform = entity.GetComponent<TransformComponent>();

			SDL_Surface* surface = TTF_RenderText_Blended(assetManager.GetFont(text.assetID), text.text.c_str(), text.color);
			SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
			SDL_FreeSurface(surface);

			int textWidth = 0;
			int textHeight = 0;

			SDL_QueryTexture(texture, NULL, NULL, &textWidth, &textHeight);

			SDL_Rect destRect = {
				static_cast<int>(transform.position.x - (text.isFixed ? 0 : camera.x)),
				static_cast<int>(transform.position.y - (text.isFixed ? 0 : camera.y)),
				textWidth, textHeight
			};

			SDL_RenderCopy(renderer, texture, NULL, &destRect);
			SDL_DestroyTexture(texture);
		}
	}
};
