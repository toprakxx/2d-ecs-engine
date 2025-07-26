#pragma once
#include <bitset>
#include <SDL_scancode.h>

class InputManager {
public:
	void BeginFrame();
	void KeyPressed(SDL_Scancode k);
	void KeyReleased(SDL_Scancode k);
	bool isKeyDown(SDL_Scancode k);
	bool isKeyPressed(SDL_Scancode k);
	bool isKeyReleased(SDL_Scancode k);

private:
	std::bitset<SDL_NUM_SCANCODES> currentFrame;
	std::bitset<SDL_NUM_SCANCODES> lastFrame;
};

constexpr SDL_Scancode KEY_A = SDL_SCANCODE_A;
constexpr SDL_Scancode KEY_B = SDL_SCANCODE_B;
constexpr SDL_Scancode KEY_C = SDL_SCANCODE_C;
constexpr SDL_Scancode KEY_D = SDL_SCANCODE_D;
constexpr SDL_Scancode KEY_E = SDL_SCANCODE_E;
constexpr SDL_Scancode KEY_F = SDL_SCANCODE_F;
constexpr SDL_Scancode KEY_G = SDL_SCANCODE_G;
constexpr SDL_Scancode KEY_H = SDL_SCANCODE_H;
constexpr SDL_Scancode KEY_I = SDL_SCANCODE_I;
constexpr SDL_Scancode KEY_J = SDL_SCANCODE_J;
constexpr SDL_Scancode KEY_K = SDL_SCANCODE_K;
constexpr SDL_Scancode KEY_L = SDL_SCANCODE_L;
constexpr SDL_Scancode KEY_M = SDL_SCANCODE_M;
constexpr SDL_Scancode KEY_N = SDL_SCANCODE_N;
constexpr SDL_Scancode KEY_O = SDL_SCANCODE_O;
constexpr SDL_Scancode KEY_P = SDL_SCANCODE_P;
constexpr SDL_Scancode KEY_Q = SDL_SCANCODE_Q;
constexpr SDL_Scancode KEY_R = SDL_SCANCODE_R;
constexpr SDL_Scancode KEY_S = SDL_SCANCODE_S;
constexpr SDL_Scancode KEY_T = SDL_SCANCODE_T;
constexpr SDL_Scancode KEY_U = SDL_SCANCODE_U;
constexpr SDL_Scancode KEY_V = SDL_SCANCODE_V;
constexpr SDL_Scancode KEY_W = SDL_SCANCODE_W;
constexpr SDL_Scancode KEY_X = SDL_SCANCODE_X;
constexpr SDL_Scancode KEY_Y = SDL_SCANCODE_Y;
constexpr SDL_Scancode KEY_Z = SDL_SCANCODE_Z;

constexpr SDL_Scancode KEY_1 = SDL_SCANCODE_1;
constexpr SDL_Scancode KEY_2 = SDL_SCANCODE_2;
constexpr SDL_Scancode KEY_3 = SDL_SCANCODE_3;
constexpr SDL_Scancode KEY_4 = SDL_SCANCODE_4;
constexpr SDL_Scancode KEY_5 = SDL_SCANCODE_5;
constexpr SDL_Scancode KEY_6 = SDL_SCANCODE_6;
constexpr SDL_Scancode KEY_7 = SDL_SCANCODE_7;
constexpr SDL_Scancode KEY_8 = SDL_SCANCODE_8;
constexpr SDL_Scancode KEY_9 = SDL_SCANCODE_9;
constexpr SDL_Scancode KEY_0 = SDL_SCANCODE_0;

constexpr SDL_Scancode KEY_RETURN = SDL_SCANCODE_RETURN;
constexpr SDL_Scancode KEY_ESCAPE = SDL_SCANCODE_ESCAPE;
constexpr SDL_Scancode KEY_BACKSPACE = SDL_SCANCODE_BACKSPACE;
constexpr SDL_Scancode KEY_TAB = SDL_SCANCODE_TAB;
constexpr SDL_Scancode KEY_SPACE = SDL_SCANCODE_SPACE;
