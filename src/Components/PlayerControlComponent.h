#pragma once

struct PlayerControlComponent {
	PlayerControlComponent(int v = 0)
	: jumpSpeed(v)
	{}

	int jumpSpeed;
};
