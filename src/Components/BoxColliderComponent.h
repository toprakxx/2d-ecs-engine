#pragma once
#include <glm/glm.hpp>

struct BoxColliderComponent {
	BoxColliderComponent(
		int _width = 16,
		int _height = 16,
		glm::vec2 _offset = glm::vec2(0)
	) : 
		width(_width),
		height(_height),
		offset(_offset) {}

	int width;
	int height;
	glm::vec2 offset;
	bool isEnabled;
	bool inCollision;
};
