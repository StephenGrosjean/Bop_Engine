#include "..\Game.h"
#include "..\Time.h"

Game* game = nullptr;
#define XRES 640 //X resolution
#define YRES 640 //Y resolution
#define FPS  60	 //Max FPS

int main(int argc, char* argv[]) 
{
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	game = new Game();
	game->Init("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, XRES, YRES, false);
	
	//Main Game Loop
	while (game->GetRunning())
	{
		frameStart = SDL_GetTicks();

		game->HandleEvents();
		game->Update();
		game->Render();
		
		frameTime = SDL_GetTicks() - frameStart;
		game->time->SetDeltaTime(frameTime);

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->Clean();

	return 0;
}