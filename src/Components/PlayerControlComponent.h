#pragma once

struct PlayerControlComponent {
	PlayerControlComponent(int v = 0, int highGrav = 0, int lowGrav = 0)
	: 
		jumpSpeed(v),
		highGrav(highGrav),
		lowGrav(lowGrav)
	{}

	int jumpSpeed;
	int highGrav;
	int lowGrav;
};
