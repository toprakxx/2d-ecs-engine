#pragma once

struct PlayerControlComponent {
	float playerMoveSpeed;

	PlayerControlComponent(
		float _moveSpeed = 0
	) :
		playerMoveSpeed(_moveSpeed)
	{}
};
