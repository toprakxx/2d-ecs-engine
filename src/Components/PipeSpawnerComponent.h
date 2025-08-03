#pragma once

struct PipeSpawnerComponent {
	PipeSpawnerComponent(
		int gap = 0,
		int pipeRightShift = 0,
		int pipeMoveSpeed = 0,
		int high = 0,
		int low = 0,
		double spawnTimer = 0,
		float pipeLife = 1
	) :
		gap(gap),
		pipeRightShift(pipeRightShift),
		pipeMoveSpeed(pipeMoveSpeed),
		high(high),
		low(low),
		spawnTimer(spawnTimer),
		currentTimer(0),
		pipeLife(pipeLife)
	{}

	int gap;
	int pipeRightShift;
	int pipeMoveSpeed;
	int high;
	int low;
	double spawnTimer;
	double currentTimer;
	float pipeLife;
};
