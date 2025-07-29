#pragma once
#include "../Event.h"
#include "../../ECS/ECS.h"

class ButtonClickedEvent : public Event {
public:
	ButtonClickedEvent(Entity a) : a(a) {}
	Entity a;
};
