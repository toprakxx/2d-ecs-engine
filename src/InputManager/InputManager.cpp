#include "./InputManager.h"
#include "SDL_scancode.h"

void InputManager::BeginFrame() {
	//Record the kbCurrentFramerrent frame as the last frame on the start of each frame
	kbLastFrame = kbCurrentFrame;
	mouseLastFrame = mouseCurrentFrame;
}

void InputManager::KeyPressed(SDL_Scancode k) {
	kbCurrentFrame.set(k);
}

void InputManager::KeyReleased(SDL_Scancode k) {
	kbCurrentFrame.reset(k);
}

bool InputManager::isKeyDown(SDL_Scancode k) const {
	return kbCurrentFrame.test(k);
}

bool InputManager::isKeyPressed(SDL_Scancode k) const {
	return (kbCurrentFrame.test(k) and !kbLastFrame.test(k));
}

bool InputManager::isKeyReleased(SDL_Scancode k) const {
	return (!kbCurrentFrame.test(k) and kbLastFrame.test(k));
}

void  InputManager::MousePressed(Uint8 b){
	mouseCurrentFrame.set(b);
}

void  InputManager::MouseReleased(Uint8 b){
	mouseCurrentFrame.reset(b);
}

bool  InputManager::isMouseDown(Uint8 b) const {
	return mouseCurrentFrame.test(b);
}

bool  InputManager::isMousePressed(Uint8 b) const {
	return (mouseCurrentFrame.test(b) and !mouseLastFrame.test(b));
}

bool  InputManager::isMouseReleased(Uint8 b) const {
	return (!mouseCurrentFrame.test(b) and mouseLastFrame.test(b));
}

void InputManager::SetMousePosition(int x, int y) {
	mouseXPos = x; mouseYPos = y;
}

glm::vec2 InputManager::GetMousePosition() const {
	return glm::vec2(static_cast<float>(mouseXPos), static_cast<float>(mouseYPos));
}
