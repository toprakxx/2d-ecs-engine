#include <SDL_image.h>
#include "./AssetManager.h"
#include "../Logger/Logger.h"
#include "SDL_render.h"
#include "SDL_surface.h"
#include "SDL_ttf.h"

AssetManager::AssetManager() {
	Logger::Confirm("Asset Manager consturcted.");
}

AssetManager::~AssetManager() {
	Logger::Confirm("Asset Manager destructed.");
}

void AssetManager::ClearAssets() { 
	for (auto texture : textures) {
		SDL_DestroyTexture(texture.second);
	}
	textures.clear();

	for (auto font : fonts) {
		TTF_CloseFont(font.second);
	}
	fonts.clear();
}

void AssetManager::AddTexture(SDL_Renderer* renderer, const std::string_view& assetName, const std::string& filePath) { 
	SDL_Surface* surface = IMG_Load((ASSETS_PATH + filePath).c_str());
	if(!surface) Logger::Err("Filepath for asset does not exits: " + filePath);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	textures.emplace(assetName, texture);
}

SDL_Texture* AssetManager::GetTexture(const std::string& assetName) { 
	return textures.at(assetName);
}

void AssetManager::AddFont(const std::string_view& fontName, const std::string& filePath, int fontSize) {
	TTF_Font* font = TTF_OpenFont((ASSETS_PATH + filePath).c_str(), fontSize);
	if(!font) Logger::Err("Filepath for font does not exist: " + filePath);
	fonts.emplace(fontName, font);
}

TTF_Font* AssetManager::GetFont(const std::string& fontName) { 
	return fonts.at(fontName);
}
