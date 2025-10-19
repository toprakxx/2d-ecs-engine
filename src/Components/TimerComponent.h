#pragma once

struct TimerComponent {
	TimerComponent(float _max = 100) : 
		maxSeconds(_max),
		bridgeCollapsed(false)
	{
		currentSeconds = maxSeconds;
	}

	float maxSeconds;
	float currentSeconds;
	bool bridgeCollapsed;
};
