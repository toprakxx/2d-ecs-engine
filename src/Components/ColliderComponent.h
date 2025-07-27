#pragma once
#include <glm/glm.hpp>
#include "../Utils.hpp" 

struct ColliderComponent 
{ 
	ColliderComponent( 
		Collider _type = Box,
		int _width_radius = 16,
		int _height = 16,
		glm::vec2 _offset = glm::vec2(0)
	) : 
		type(_type),
		w_r(_width_radius),
		h(_height),
		offset(_offset) {}

	Collider type;
	int w_r;
	int h;
	glm::vec2 offset;
	bool inCollision;
};
