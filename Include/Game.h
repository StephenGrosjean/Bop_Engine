#ifndef Game_h
#define Game_h
#include "SDL.h"
#include <iostream>

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

	static SDL_Renderer* renderer;

private:
	int counter = 0;
	bool isRunning = false;
	SDL_Window* window;
};



#endif /* Game_h */
