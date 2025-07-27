#pragma once
#include <glm/glm.hpp>
#include "../Utils.hpp" 

struct ColliderComponent 
{ 
	ColliderComponent( 
		Collider _type = Box,
		glm::vec2 _offset = glm::vec2(0),
		int _width_2radius = 16,
		int _height = 16
	) : 
		type(_type),
		offset(_offset),
		width_2r(_width_2radius),
		height(_height) {}

	Collider type;
	glm::vec2 offset;
	int width_2r;
	int height;
	bool inCollision;
};
