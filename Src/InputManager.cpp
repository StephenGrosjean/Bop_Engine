#include "..\InputManager.h"
#include "..\Game.h"

InputManager::InputManager()
{
	//Player 1 keys
	keys.emplace(SDLK_w, State::None);
	keys.emplace(SDLK_s, State::None);
	keys.emplace(SDLK_a, State::None);
	keys.emplace(SDLK_d, State::None);

	//Player 2 keys
	keys.emplace(SDLK_UP, State::None);
	keys.emplace(SDLK_DOWN, State::None);
	keys.emplace(SDLK_LEFT, State::None);
	keys.emplace(SDLK_RIGHT, State::None);

	//Start Key
	keys.emplace(SDLK_SPACE, State::None);
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

SDL_Keycode& InputManager::GetInput(Direction direction, int playerID)
{
	if (playerID == 0)
	{
		switch (direction) {
			case Direction::Up:
				return player1_Up;
			case Direction::Down:
				return player1_Down;
			case Direction::Left:
				return player1_Left;
			case Direction::Right:
				return player1_Right;
		}
	}

	if (playerID == 1)
	{
		switch (direction)
		{
		case Direction::Up:
			return player2_Up;
		case Direction::Down:
			return player2_Down;
		case Direction::Left:
			return player2_Left;
		case Direction::Right:
			return player2_Right;
		}
	}
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
		case SDL_QUIT:
			isQuit = true;
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
