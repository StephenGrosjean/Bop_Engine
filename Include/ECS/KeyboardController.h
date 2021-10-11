#pragma once
#include "Game.h"
#include "ECS.h"
#include "Components.h"

class KeyboardController : public Component
{
public:
	TransformComponent* transform;
	SpriteComponent* sprite;

	void Init() override
	{
		transform = &entity->GetComponent<TransformComponent>();
		sprite = &entity->GetComponent<SpriteComponent>();
	}

	void Update() override
	{
		if (Game::inputManager->GetKeyDown(SDLK_w))
		{
			transform->velocity.y = -1;
			sprite->Play("Walk");
		}
		else if (Game::inputManager->GetKeyUp(SDLK_w))
		{
			transform->velocity.y = 0;
			sprite->Play("Idle");
		}

		if (Game::inputManager->GetKeyDown(SDLK_s))
		{
			transform->velocity.y = 1;
			sprite->Play("Walk");
		}
		else if (Game::inputManager->GetKeyUp(SDLK_s))
		{
			transform->velocity.y = 0;
			sprite->Play("Idle");
		}

		if (Game::inputManager->GetKeyDown(SDLK_a))
		{
			transform->velocity.x = -1;
			sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
			sprite->Play("Walk");
		}
		else if (Game::inputManager->GetKeyUp(SDLK_a))
		{
			transform->velocity.x = 0;
			sprite->spriteFlip = SDL_FLIP_NONE;
			sprite->Play("Idle");
		}

		if (Game::inputManager->GetKeyDown(SDLK_d))
		{
			transform->velocity.x = 1;
			sprite->Play("Walk");
		}
		else if (Game::inputManager->GetKeyUp(SDLK_d))
		{
			transform->velocity.x = 0;
			sprite->Play("Idle");
		}

	}


};
