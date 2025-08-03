#pragma once 
#include <SDL.h>
#include <numeric>
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
			auto& text = entity.GetComponent<TextComponent>();
			const auto& transform = entity.GetComponent<TransformComponent>();

			SDL_Surface* surface = TTF_RenderText_Blended(assetManager.GetFont(text.assetID), text.text.c_str(), text.color);
			SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
			SDL_FreeSurface(surface);

			int textWidth = 0;
			int textHeight = 0;

			SDL_QueryTexture(texture, NULL, NULL, &textWidth, &textHeight);

			int destX = 0;

			switch (text.alignment) {
				case TopLeft:
					destX = transform.position.x;
					break;
				case TopCenter:
					destX = transform.position.x - textWidth/2.0;
					break;
				case TopRight:
					destX = transform.position.x - textWidth;
					break;
			}

			SDL_Rect destRect = {
				static_cast<int>(destX - (text.isFixed ? 0 : camera.x)),
				static_cast<int>(transform.position.y - (text.isFixed ? 0 : camera.y)),
				textWidth, textHeight
			};

			SDL_RenderCopy(renderer, texture, NULL, &destRect);
			SDL_DestroyTexture(texture);
		}
	}
};
