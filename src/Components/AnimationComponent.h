#pragma once

struct AnimationComponent {
	AnimationComponent(int frameCount = 0, int frameRate = 12)
	:
	animationFrameCount(frameCount), 
	animationFrameRate(frameRate),
	secondsPerAnimationFrame(1.0f/animationFrameRate),
	frameTimer(secondsPerAnimationFrame),
	currentFrame(0) {} 

	int animationFrameCount;
	int animationFrameRate;
	double secondsPerAnimationFrame;
	double frameTimer;
	int currentFrame;
};
