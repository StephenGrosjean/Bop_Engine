#include "InputManager.h"
#include "Game.h"

InputManager::InputManager()
{
	//Player 1 keys
	keys.emplace(SDLK_w, State::None);
	keys.emplace(SDLK_s, State::None);
	keys.emplace(SDLK_a, State::None);
	keys.emplace(SDLK_d, State::None);
}

InputManager::~InputManager()
{

}

bool InputManager::GetKeyDown(SDL_Keycode key)
{
	return keys[key] == State::Up;
}

bool InputManager::GetKeyUp(SDL_Keycode key)
{
	return keys[key] == State::Down;
}

void InputManager::Update()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			keys[event.key.keysym.sym] = State::Up;
			break;
		case SDL_KEYUP:
			keys[event.key.keysym.sym] = State::Down;
			break;
		default:
			break;
		}
	}
}



void InputManager::Reset()
{
	for (auto const& [key, val] : keys)
	{
		if(keys[key] == State::Down)
			keys[key] = State::None;
	}
}
