#pragma once
#include <string>
#include <SDL.h>

struct SpriteComponent {
	SpriteComponent(
		std::string _assetName = "",
		int _width = 0,
		int _height = 0,
		double _spriteScale = 1.0,
		int _zIndex = 0,
		int _srcRectX = 0,
		int _srcRectY = 0,
		bool _isFixed = false
	) :
		assetName(_assetName),
		width(_width), 
		height(_height), 
		spriteScale(_spriteScale),
		zIndex(_zIndex),
		isFixed(_isFixed),
		srcRect(_srcRectX, _srcRectY, width, height),
		flip(SDL_FLIP_NONE)
	{}

	std::string assetName;
	int width;
	int height;
	double spriteScale;
	int zIndex;
	SDL_Rect srcRect;
	bool isFixed;
	SDL_RendererFlip flip;
};
