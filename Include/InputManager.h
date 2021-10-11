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

	InputManager();
	~InputManager();

	bool GetKeyDown(SDL_Keycode key);
	bool GetKeyUp(SDL_Keycode key);
	void Update();
	void Reset();

protected:
	std::map<SDL_Keycode, State> keys;
};