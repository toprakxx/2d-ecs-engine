#pragma once
#include <string>
#include "../Event.h"

class SoundEffectEvent : public Event {
public:
	SoundEffectEvent(std::string_view sfxName) : sfxName(sfxName){};

	std::string sfxName;
};
