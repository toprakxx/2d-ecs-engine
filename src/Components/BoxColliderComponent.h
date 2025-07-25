#pragma once
#include <glm/glm.hpp>
#include "../Utils.hpp" 

struct ColliderComponent 
{ 
	ColliderComponent( 
		Collider _type = Box,
		int _width = 16,
		int _height = 16,
		glm::vec2 _offset = glm::vec2(0)
	) : 
		type(_type),
		width(_width),
		height(_height),
		offset(_offset) {}

	Collider type;
	int width;
	int height;
	glm::vec2 offset;
	bool isEnabled;
	bool inCollision;
};
