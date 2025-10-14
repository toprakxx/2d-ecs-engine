#pragma once
#include <array>
#include <glm/glm.hpp>
#include <initializer_list>
#include "../ECS/ECS.h"

const int MAX_CHILD_NUM = 16;

struct Child {
	Entity entity;
	glm::vec2 offset;
};

struct ParentComponent {
	ParentComponent(std::initializer_list<Child> init = {}) : childCount(0){
		childCount = init.size();
		std::copy(init.begin(), init.end(), children.begin());
	};

	std::array<Child,MAX_CHILD_NUM> children;
	int childCount;
};
