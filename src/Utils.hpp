#pragma once
#include <SDL.h>

// #define DEBUG

enum Tag {
	Player,
	Enemy,
	Obstacle,
	Score,
	Death,
	PlayerInteractionCast,
	Collectible,
};

enum Collider {
	Box,
	Circle,
};

const unsigned int VECTOR_INIT = 300;
const unsigned int MAX_COMPONENTS = 32;
const unsigned int MAX_TAGS = 32;
const unsigned int MAX_MOUSE_BUTTONS = 8;

const int MAX_FPS = 200;
const int MIN_MS_PER_FRAME = 1000 / MAX_FPS;

const int SCALE_FACTOR_32 = 2;
const int SCALE_FACTOR_16 = 10;

const int PLAYER_INTERACTION_WIDTH = 60;
const int PLAYER_INTERACTION_HEIGHT = PLAYER_INTERACTION_WIDTH;
