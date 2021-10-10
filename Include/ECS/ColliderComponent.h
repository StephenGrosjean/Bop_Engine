#pragma once
#include <string>
#include "SDL.h"
#include "Components.h"
#include "TextureManager.h"

class ColliderComponent : public Component
{
public:
	SDL_Rect collider;
	std::string tag;

	SDL_Texture* texture;
	SDL_Rect srcRect;
	SDL_Rect destRect;

	TransformComponent* transform;

	ColliderComponent()
	{
		tag = "Default";
	}

	ColliderComponent(std::string tag)
	{
		this->tag = tag;
	}

	ColliderComponent(std::string tag, Vec2i position, int size)
	{
		this->tag = tag;
		collider.x = position.x;
		collider.y = position.y;
		collider.h = collider.w = size;
	}

	void Init() override
	{
		if (!entity->HasComponent<TransformComponent>())
		{
			entity->AddComponent<TransformComponent>();
		}
		transform = &entity->GetComponent<TransformComponent>();

		texture = TextureManager::LoadTexture("Assets/ColliderTexture.png");
		srcRect = { 0,0,32,32 };
		destRect = { collider.x, collider.y, collider.w, collider.h };
	}

	void Update() override
	{
		if (tag != "Terrain")
		{
			collider.x = static_cast<int>(transform->position.x);
			collider.y = static_cast<int>(transform->position.y);
			collider.w = transform->width * transform->scale;
			collider.h = transform->height * transform->scale;
		}
		
		destRect.x = collider.x - Game::camera.x;
		destRect.y = collider.y - Game::camera.y;
	}

	void Draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
	}
};