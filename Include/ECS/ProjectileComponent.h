#pragma once
#include "ECS.h"
#include "Components.h"
#include "..\Vector2D.h"

class ProjectileComponent : public Component
{
public:
	ProjectileComponent(Vec2f velocity) : velocity(velocity)
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
		timer += Game::time->DeltaTime();
		if (timer >= timeBeforeDestruction) entity->Destroy();

		/*if (transform->position.x > Game::camera.x + Game::camera.w ||
				transform->position.x < Game::camera.x ||
				transform->position.y > Game::camera.y + Game::camera.h ||
				transform->position.y < Game::camera.y)
		{
			entity->Destroy();
		}*/
	}
private:
	TransformComponent* transform;
	int timeBeforeDestruction = 200;
	int distance = 0;
	float timer = 0.0f;
	Vec2f velocity;

};