#pragma once
#include "ECS.h"
#include "Components.h"
#include "..\Vector2D.h"

class ProjectileComponent : public Component
{
public:
	ProjectileComponent(int range, int speed, Vec2f velocity) : range(range), speed(speed), velocity(velocity)
	{

	}

	~ProjectileComponent() {}

	void Init() override
	{
		transform = &entity->GetComponent<TransformComponent>();
		transform->velocity = velocity;
	}

	void Update() override
	{
		distance += speed;

		if (distance > range)
		{
			entity->Destroy();
		}
		else if(transform->position.x > Game::camera.x + Game::camera.w || 
				transform->position.x < Game::camera.x ||
				transform->position.y > Game::camera.y + Game::camera.h ||
				transform->position.y < Game::camera.y)
		{
			entity->Destroy();
		}
	}
private:
	TransformComponent* transform;
	int range = 0;
	int speed = 0;
	int distance = 0;
	Vec2f velocity;

};