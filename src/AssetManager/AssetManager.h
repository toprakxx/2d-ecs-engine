#pragma once
#include <string>
#include <string_view>
#include <SDL.h>
#include <SDL_ttf.h>
#include <unordered_map>
#include "SDL_mixer.h"
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

	void AddSFX(const std::string_view& sfxName, const std::string& filePath);
	Mix_Chunk* GetSFX(const std::string& sfxName);

private:
	std::unordered_map<std::string, SDL_Texture*> textures;
	std::unordered_map<std::string, TTF_Font*> fonts;
	std::unordered_map<std::string, Mix_Chunk*> soundEffects;
};
