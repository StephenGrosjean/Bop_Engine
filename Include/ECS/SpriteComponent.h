#pragma once
#include "SDL.h"
#include "TransformComponent.h"
#include "Animation.h"
#include "..\TextureManager.h"
#include "..\Game.h"
#include <map>

class SpriteComponent : public Component
{
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect;
	SDL_Rect destRect;

	bool animated = false;
	int frames = 0;
	int frameDelay = 100;


public:
	int animationIndex = 0;

	std::map<const char*, Animation> animations;

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent() = default;
	SpriteComponent(std::string textureID)
	{
		SetTexture(textureID);
	}

	SpriteComponent(std::string textureID, bool isAnimated)
	{
		animated = isAnimated;

		Animation idle = Animation(0, 3, 300);
		Animation walk = Animation(1, 4, 100);

		animations.emplace("Idle", idle);
		animations.emplace("Walk", walk);

		Play("Idle");
		SetTexture(textureID);
	}

	~SpriteComponent()
	{

	}

	void Init() override
	{
		transform = &entity->GetComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;
	}

	void Update() override
	{
		if (animated)
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / frameDelay) % frames);
		}

		srcRect.y = animationIndex * transform->height;

		destRect.x = (int)transform->position.x - Game::camera.x;
		destRect.y = (int)transform->position.y - Game::camera.y;
		destRect.w = transform->width * transform->scale.x;
		destRect.h = transform->height * transform->scale.y;
	}

	void Draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
	}

	void SetTexture(std::string textureID)
	{
		texture = Game::assetManager->GetTexture(textureID);
	}

	void Play(const char* animName)
	{
		frames = animations[animName].frames;
		animationIndex = animations[animName].index;
		frameDelay = animations[animName].frameDelay;
	}
};