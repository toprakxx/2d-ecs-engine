#pragma once
#include "glm/fwd.hpp"
#include <functional>
#include <glm/glm.hpp>

struct UIButtonComponent {
	UIButtonComponent(int _width = 0, int _height = 0, std::function<void()> _func = [](){}, glm::vec2 _offset = glm::vec2(0))
	: width(_width), height(_height), callback(_func), offset(_offset), mouseHover(false) {}

	int width;
	int height;
	std::function<void()> callback;
	glm::vec2 offset;
	bool mouseHover;
};
