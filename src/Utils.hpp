#pragma once

enum Tag {
	Player,
	Enemy,
	Obstacle
};

const unsigned int VECTOR_INIT = 300;
const unsigned int MAX_COMPONENTS = 32;
const unsigned int MAX_TAGS = 32;

const int MAX_FPS = 160;
const int MIN_MS_PER_FRAME = 1000 / MAX_FPS;
