#pragma once
#include "../../ECS/ECS.h"
#include "../Event.h"

class AnimationDoneEvent : public Event {
public:
	AnimationDoneEvent(Entity a, std::string_view name)
	: entity(a), animationName(name) {}

	Entity entity;
	std::string animationName;
};
