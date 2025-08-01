#pragma once
#include "../../ECS/ECS.h"
#include "../Event.h"

class CollisionEnterEvent : public Event {
public:
	CollisionEnterEvent(Entity a , Entity b) : a(a), b(b) {}

	Entity a, b;
};
