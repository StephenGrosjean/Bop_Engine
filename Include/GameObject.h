#pragma once
#include "Game.h"
#include "TextureManager.h"

class GameObject
{
public:
	GameObject(const char* textureSheet, int x, int y);
	~GameObject();

	void Update();
	void Render();

private:
	int xPos;
	int yPos;

	SDL_Texture* objTexture;
	SDL_Rect srcRect;
	SDL_Rect destRect;
};