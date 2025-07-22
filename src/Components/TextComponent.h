#pragma once 
#include "SDL_pixels.h"
#include "glm/fwd.hpp"
#include <string>
#include <SDL.h>
#include <glm/glm.hpp>


struct TextComponent {
	glm::vec2 position;
	std::string text;
	std::string assetID;
	SDL_Color color;
	bool isFixed;

	TextComponent(
		glm::vec2 _position = glm::vec2(0),
		std::string _text = "lorem ipsum",
		std::string _assetID = "",
		SDL_Color _color = {0, 0, 0},
		bool _isFixed = true
	) :
	position(_position),
	text(_text),
	assetID(_assetID),
	color(_color),
	isFixed(_isFixed)
	{}
};
