#pragma once
#include "..\Vector2D.h"

class TransformComponent : public Component
{
public:

	Vec2f position;
	Vec2f velocity;

	int height = 32;
	int width = 32;
	Vec2i scale = Vec2i::one;

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
		scale = Vec2i::one * sc;
	}

	TransformComponent(float x, float y, int h, int w, int sc)
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = Vec2i::one * sc;
	}

	TransformComponent(float x, float y, int h, int w, Vec2i sc)
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}

	void Init() override
	{
		velocity = Vec2f::zero;
	}

	void Update() override
	{
		position.x += static_cast<int>(velocity.x * speed);
		position.y += static_cast<int>(velocity.y * speed);
	}
};