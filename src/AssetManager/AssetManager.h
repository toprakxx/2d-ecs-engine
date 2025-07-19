#pragma once
#include <string>
#include <string_view>
#include <SDL.h>
#include <SDL_ttf.h>
#include <unordered_map>
#include "SDL_render.h"

class AssetManager {
public:
	AssetManager();
	~AssetManager();

	void ClearAssets();
	void AddTexture(SDL_Renderer* renderer, const std::string_view& assetName, const std::string& filePath);
	SDL_Texture* GetTexture(const std::string& assetName);
	void AddFont(const std::string_view& fontName, const std::string& filePath, int fontSize);
	TTF_Font* GetFont(const std::string& fontName);

private:
	std::unordered_map<std::string, SDL_Texture*> textures;
	std::unordered_map<std::string, TTF_Font*> fonts;
};
