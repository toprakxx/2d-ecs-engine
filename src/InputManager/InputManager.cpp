#include "./InputManager.h"
#include "SDL_scancode.h"

void InputManager::BeginFrame() {
	//Record the current frame as the last frame on the start of each frame
	lastFrame = currentFrame;
}

void InputManager::KeyPressed(SDL_Scancode k) {
	currentFrame.set(k);
}

void InputManager::KeyReleased(SDL_Scancode k) {
	currentFrame.reset(k);
}

bool InputManager::isKeyDown(SDL_Scancode k){
	return currentFrame.test(k);
}

bool InputManager::isKeyPressed(SDL_Scancode k){
	return (currentFrame.test(k) and !lastFrame.test(k));
}

bool InputManager::isKeyReleased(SDL_Scancode k){
	return (!currentFrame.test(k) and lastFrame.test(k));
}
