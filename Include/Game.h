#ifndef Game_h
#define Game_h
#include "SDL.h"
#include <iostream>
#include <vector>
#include "Vector2D.h"

class ColliderComponent;

class Game {

public:
	Game();
	~Game();

	void Init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);
	
	void HandleEvents();
	void Update();
	void Render();
	void Clean();
	
	bool Running() { return isRunning; }

	static void AddTile(int id, Vec2i position);
	static SDL_Renderer* renderer;
	static SDL_Event event;
	static std::vector<ColliderComponent*> colliders;

private:
	int counter = 0;
	bool isRunning = false;
	SDL_Window* window;
};



#endif /* Game_h */
