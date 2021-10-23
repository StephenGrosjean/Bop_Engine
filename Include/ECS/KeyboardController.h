#pragma once
#include "..\Game.h"
#include "ECS.h"
#include "Components.h"

class KeyboardController : public Component
{
public:
	TransformComponent* transform;
	SpriteComponent* sprite;
	InputManager* inputManager;

	KeyboardController(int playerID) : playerID(playerID)
	{};
	~KeyboardController() {};

	void Init() override
	{
		transform = &entity->GetComponent<TransformComponent>();
		sprite = &entity->GetComponent<SpriteComponent>();
		inputManager = Game::inputManager;
	}

	void Update() override
	{
		if (inputManager->GetKeyDown(inputManager->GetInput(InputManager::Direction::Up, playerID)))
		{
			transform->velocity.y = -1;
			sprite->Play("Walk");
		}
		else if (Game::inputManager->GetKeyUp(inputManager->GetInput(InputManager::Direction::Up, playerID)))
		{
			transform->velocity.y = 0;
			sprite->Play("Idle");
		}

		if (Game::inputManager->GetKeyDown(inputManager->GetInput(InputManager::Direction::Down, playerID)))
		{
			transform->velocity.y = 1;
			sprite->Play("Walk");
		}
		else if (Game::inputManager->GetKeyUp(inputManager->GetInput(InputManager::Direction::Down, playerID)))
		{
			transform->velocity.y = 0;
			sprite->Play("Idle");
		}

		if (Game::inputManager->GetKeyDown(inputManager->GetInput(InputManager::Direction::Left, playerID)))
		{
			transform->velocity.x = -1;
			sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
			sprite->Play("Walk");
		}
		else if (Game::inputManager->GetKeyUp(inputManager->GetInput(InputManager::Direction::Left, playerID)))
		{
			transform->velocity.x = 0;
			sprite->spriteFlip = SDL_FLIP_NONE;
			sprite->Play("Idle");
		}

		if (Game::inputManager->GetKeyDown(inputManager->GetInput(InputManager::Direction::Right, playerID)))
		{
			transform->velocity.x = 1;
			sprite->Play("Walk");
		}
		else if (Game::inputManager->GetKeyUp(inputManager->GetInput(InputManager::Direction::Right, playerID)))
		{
			transform->velocity.x = 0;
			sprite->Play("Idle");
		}

		transform->velocity *= Game::difficultyManager->currentPlayerSpeed;

	}

private:
	int playerID;
};
