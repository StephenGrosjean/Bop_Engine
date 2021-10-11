#pragma once
#include "SDL.h"
#include <string>
#include <map>
class InputManager
{

public:
	enum class State
	{
		Up,
		Down,
		None,
	};

	enum class Direction
	{
		Up,
		Down,
		Left,
		Right
	};

	InputManager();
	~InputManager();

	bool GetKeyDown(SDL_Keycode key);
	bool GetKeyUp(SDL_Keycode key);
	
	SDL_Keycode& GetInput(Direction direction, int playerID);

	void Update();
	void Reset();

protected:
	std::map<SDL_Keycode, State> keys;

	SDL_Keycode player1_Up = SDLK_w;
	SDL_Keycode player1_Down = SDLK_s;
	SDL_Keycode player1_Left = SDLK_a;
	SDL_Keycode player1_Right = SDLK_d;

	SDL_Keycode player2_Up = SDLK_UP;
	SDL_Keycode player2_Down = SDLK_DOWN;
	SDL_Keycode player2_Left = SDLK_LEFT;
	SDL_Keycode player2_Right = SDLK_RIGHT;

};