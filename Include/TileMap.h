#pragma once
#include "Game.h"

class TileMap
{
public:
	TileMap();
	~TileMap();


	static const int rows = 20;
	static const int columns = 25;

	void Load(int arr[rows][columns]);
	void Draw();

private:
	SDL_Rect src;
	SDL_Rect dest;

	SDL_Texture* dirt;
	SDL_Texture* grass;
	SDL_Texture* water;

	int map[rows][columns];
};