#pragma once
#include "ECS.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "SDL.h"


class TileComponent : public Component
{
public:

	const char* grassPath = "Assets/grass.png";
	const char* dirtPath = "Assets/dirt.png";
	const char* waterPath = "Assets/water.png";

	TransformComponent* transform;
	SpriteComponent* sprite;

	SDL_Rect tileRect;
	int tileID;
	const char* path;

	TileComponent() {};
	TileComponent(Vec2i position, Vec2i size, int id)
	{
		tileRect.x = position.x;
		tileRect.y = position.y;
		tileRect.w = size.x;
		tileRect.h = size.y;
		tileID = id;

		switch (tileID)
		{
			case 0:
				path = dirtPath;
				break;
			case 1:
				path = grassPath;
				break;
			case 2:
				path = waterPath;

				break;
			default:
				break;
		}
	}

	void Init() override
	{
		entity->AddComponent<TransformComponent>(tileRect.x, tileRect.y, tileRect.w, tileRect.h, 1);
		transform = &entity->GetComponent<TransformComponent>();
		
		entity->AddComponent<SpriteComponent>(path);
		sprite = &entity->GetComponent<SpriteComponent>();
	}
};