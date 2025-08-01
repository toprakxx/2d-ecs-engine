
#pragma once
#include "../../ECS/ECS.h"
#include "../Event.h"

class CollisionExitEvent : public Event {
public:
	CollisionExitEvent(Entity a , Entity b) : a(a), b(b) {}

	Entity a, b;
};
