#pragma once
#include <string>
#include <SDL.h>

struct SpriteComponent {
	SpriteComponent(
		std::string _assetName = "",
		int _width = 0,
		int _height = 0,
		int _zIndex = 0,
		bool _isFixed = false,
		int _srcRectX = 0,
		int _srcRectY = 0
	) :
		assetName(_assetName),
		width(_width), 
		height(_height), 
		zIndex(_zIndex),
		isFixed(_isFixed),
		srcRect(_srcRectX, _srcRectY, width, height),
		flip(SDL_FLIP_NONE)
	{}

	std::string assetName;
	int width;
	int height;
	int zIndex;
	bool isFixed;
	SDL_Rect srcRect;
	SDL_RendererFlip flip;
};
