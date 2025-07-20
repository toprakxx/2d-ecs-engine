#pragma once
#include "../../ECS/ECS.h"
#include "../Event.h"

class CollisionEvent : public Event {
public:
	CollisionEvent(Entity a , Entity b) : a(a), b(b) {}
	Entity a, b;
};
