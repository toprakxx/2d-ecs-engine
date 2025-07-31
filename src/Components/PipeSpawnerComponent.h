#pragma once
#include <random>

struct PipeSpawnerComponent {
	PipeSpawnerComponent(
		int gap = 0,
		int pipeRightShift = 0,
		int pipeMoveSpeed = 0,
		int high = 0,
		int low = 0,
		double spawnTimer = 0
	) :
		gap(gap),
		pipeRightShift(pipeRightShift),
		pipeMoveSpeed(pipeMoveSpeed),
		high(high),
		low(low),
		spawnTimer(spawnTimer),
		currentTimer(spawnTimer)
	{}

	int gap;
	int pipeRightShift;
	int pipeMoveSpeed;
	int high;
	int low;
	double spawnTimer;
	double currentTimer;
};
