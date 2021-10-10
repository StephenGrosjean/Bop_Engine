#pragma once
#include "ECS.h"
#include "SDL.h"


class TileComponent : public Component
{
public:

	SDL_Texture* texture;
	SDL_Rect srcRect;
	SDL_Rect destRect;
	Vec2i position;

	TileComponent() = default;

	~TileComponent()
	{
		SDL_DestroyTexture(texture);
	}

	TileComponent(Vec2i sourceCords, Vec2i position, int tileSize, int tileScale, std::string textureID)
	{
		texture = Game::assetManager->GetTexture(textureID);
		this->position = position;

		srcRect.x = sourceCords.x;
		srcRect.y = sourceCords.y;
		srcRect.w = srcRect.h = tileSize;

		destRect.x = position.x;
		destRect.y = position.y;
		destRect.w = destRect.h = tileSize * tileScale;
	}

	void Update() override
	{
		destRect.x = position.x - Game::camera.x;
		destRect.y = position.y - Game::camera.y;
	}


	void Draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
	}

};