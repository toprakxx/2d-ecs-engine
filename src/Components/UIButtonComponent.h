#pragma once
#include <functional>

struct UIButtonComponent {
	UIButtonComponent(int _width = 0, int _height = 0, std::function<void()> _func = [](){})
	: width(_width), height(_height), callback(_func) {}

	int width;
	int height;
	std::function<void()> callback;
};
