#pragma once
#include "Vector2D.h"

class TransformComponent : public Component
{
public:

	Vec2f position;
	Vec2f velocity;

	int height = 32;
	int width = 32;
	int scale = 1;

	int speed = 3;

	TransformComponent()
	{
		position.x = 0;
		position.y = 0;
	}

	TransformComponent(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

	TransformComponent(int sc)
	{
		position.x = 0;
		position.y = 0;
		scale = sc;
	}

	TransformComponent(float x, float y, int h, int w, int sc)
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}

	void Init() override
	{
		velocity = Vec2f(0, 0);
	}

	void Update() override
	{
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}
};