#pragma once
#include "SDL.h"
#include "TransformComponent.h"
#include "Animation.h"
#include "TextureManager.h"
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
	SpriteComponent(const char* path)
	{
		SetTexture(path);
	}

	SpriteComponent(const char* path, bool isAnimated)
	{
		animated = isAnimated;

		Animation idle = Animation(0, 3, 100);
		Animation walk = Animation(1, 8, 100);

		animations.emplace("Idle", idle);
		animations.emplace("Walk", walk);

		Play("Idle");
		SetTexture(path);
	}

	~SpriteComponent()
	{
		SDL_DestroyTexture(texture);
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

		destRect.x = (int)transform->position.x;
		destRect.y = (int)transform->position.y;
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}

	void Draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
	}

	void SetTexture(const char* path)
	{
		texture = TextureManager::LoadTexture(path);
	}

	void Play(const char* animName)
	{
		frames = animations[animName].frames;
		animationIndex = animations[animName].index;
		frameDelay = animations[animName].frameDelay;
	}
};