#pragma once

struct TimerComponent {
	TimerComponent(float _max = 100) : maxSeconds(_max) {
		currentSeconds = maxSeconds;
	}

	float maxSeconds;
	float currentSeconds;
};
