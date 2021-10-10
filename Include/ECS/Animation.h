#pragma once

/// <summary>
/// Structure used to contain the animation parameters
/// </summary>
struct Animation
{
	int index;		// Current animation index
	int frames;		// Number of frames in the animation
	int frameDelay; // Delay between frames

	Animation() = default;
	Animation(int index, int frames, int frameDelay) : index(index), frames(frames), frameDelay(frameDelay){}
};