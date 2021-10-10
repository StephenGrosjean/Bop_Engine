#pragma once
#include "ECS.h"
#include "SDL.h"


class TileComponent : public Component
{
public:

	SDL_Texture* texture;
	SDL_Rect srcRect;
	SDL_Rect destRect;

	TileComponent() = default;
	~TileComponent()
	{
		SDL_DestroyTexture(texture);
	}
	TileComponent(Vec2i sourceCords, Vec2i position, const char* path)
	{
		texture = TextureManager::LoadTexture(path);

		srcRect.x = sourceCords.x;
		srcRect.y = sourceCords.y;
		srcRect.w = srcRect.h = 32;

		destRect.x = position.x;
		destRect.y = position.y;
		destRect.w = destRect.h = 64;
	}

	void Draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
	}

};