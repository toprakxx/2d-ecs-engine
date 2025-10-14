#pragma once

struct PlayerControlComponent {
	PlayerControlComponent(float playerSpeed = 0) : moveSpeed(playerSpeed) {};

	float moveSpeed;
};
