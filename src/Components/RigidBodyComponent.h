#pragma once
#include "glm/fwd.hpp"
#include <glm/glm.hpp>

struct RigidBodyComponent {
	RigidBodyComponent(glm::vec2 _velocity = glm::vec2(0), glm::vec2 _acceleration = glm::vec2(0))
	: velocity(_velocity), acceleration(_acceleration){};

	glm::vec2 velocity;
	glm::vec2 acceleration;
};
