#pragma once

class DifficultyManager
{

public:

	float currentSpawnDelay = 200;
	float currentLaserDelay = 500;
	float currentLaserSpeed = 10;
	float currentPlayerSpeed = 2;
	float speedModifier = 1.1f;
	float laserSpeedModifier = 1.02f;
	float playerSpeedModifier = 1.05f;

	void ReduceDelay()
	{
		currentLaserDelay /= speedModifier;
		currentSpawnDelay /= speedModifier;
		currentLaserSpeed *= laserSpeedModifier;
		currentPlayerSpeed *= playerSpeedModifier;
	}
	
};