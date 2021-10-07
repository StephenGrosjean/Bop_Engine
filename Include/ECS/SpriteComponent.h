#pragma once
#include "SDL.h"
#include "TransformComponent.h"

class SpriteComponent : public Component
{
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect;
	SDL_Rect destRect;

public:
	SpriteComponent() = default;
	SpriteComponent(const char* path)
	{
		texture = TextureManager::LoadTexture(path);
	}

	void Init() override
	{
		transform = &entity->GetComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = srcRect.h = 32;
		destRect.w = destRect.h = 64;
	}

	void Update() override
	{
		destRect.x = (int)transform->position.x;
		destRect.y = (int)transform->position.y;
	}

	void Draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect);
	}
};