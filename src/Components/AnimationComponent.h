#pragma once
#include <initializer_list>
#include <unordered_map>
#include <string_view>

// struct AnimationComponent {
// 	AnimationComponent(int frameCount = 0, int frameRate = 12)
// 	:
// 	animationFrameCount(frameCount), 
// 	animationFrameRate(frameRate),
// 	secondsPerAnimationFrame(1.0f/animationFrameRate),
// 	frameTimer(secondsPerAnimationFrame),
// 	currentFrame(0) {} 
//
// 	int animationFrameCount;
// 	int animationFrameRate;
// 	double secondsPerAnimationFrame;
// 	double frameTimer;
// 	int currentFrame;
// };

struct AnimationClip {
	AnimationClip(int index = 0, int frameCount = 0, bool looping = true, int frameRate = 12)
	:
	sheetIndex(index),
	animationFrameCount(frameCount), 
	isLooping(looping),
	animationFrameRate(frameRate),
	secondsPerAnimationFrame(1.0f/animationFrameRate),
	frameTimer(secondsPerAnimationFrame),
	currentFrame(0)
	{} 

	int sheetIndex;
	int animationFrameCount;
	bool isLooping;
	int animationFrameRate;
	double secondsPerAnimationFrame;
	double frameTimer;
	int currentFrame;
};

struct AnimationComponent {
	AnimationComponent() = default;
	AnimationComponent(std::initializer_list<std::pair<const std::string_view, AnimationClip>> init)
	: animations(init)
	, currentAnimation(animations.begin()->second)
	{};

	std::unordered_map<std::string_view, AnimationClip> animations;
	AnimationClip currentAnimation;
};
