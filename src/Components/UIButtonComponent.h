#pragma once

struct UIButtonComponent {
	UIButtonComponent(int _width = 0, int _height = 0)
	: width(_width), height(_height) {}

	int width;
	int height;
};
