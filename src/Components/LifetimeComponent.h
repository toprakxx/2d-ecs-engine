#pragma once

struct LifetimeComponent {
	LifetimeComponent(float timeSeconds = 1)
	: time(timeSeconds) {}

	float time; //In seconds
};
