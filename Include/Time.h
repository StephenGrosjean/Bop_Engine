#pragma once

class Time
{
	float deltaTime = 0;
public:
	void SetDeltaTime(float deltaTime)
	{
		this->deltaTime = deltaTime;
	}
	float DeltaTime(){ return deltaTime; }
};