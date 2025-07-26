#pragma once

struct PlayerControlComponent {
	PlayerControlComponent(int ps = 0)
	: playerSpeed(ps)
	{}

	int playerSpeed;
};
