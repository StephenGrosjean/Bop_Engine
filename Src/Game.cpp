#include "Game.h"
#include "TextureManager.h"
#include "TileMap.h"
#include "ECS/Components.h"
#include "Vector2D.h"

TileMap* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;

auto& player(manager.AddEntity());

Game::Game(){}
Game::~Game(){}

void Game::Init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen) 
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{		
		window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);	
		}
		isRunning = true;
	}

	map = new TileMap();

	player.AddComponent<TransformComponent>();
	player.AddComponent<SpriteComponent>("Assets/player.png");
}

void Game::HandleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
		case SDL_QUIT:
			isRunning = false;
			break;
		default:
			break;
	}
}

void Game::Update()
{
	manager.Refresh();
	manager.Update();
	player.GetComponent<TransformComponent>().position += Vec2f(5,0);

	if (player.GetComponent<TransformComponent>().position.x > 100)
	{
		std::cout << "Pos is 100" << std::endl;
	}
}

void Game::Render() 
{
	SDL_RenderClear(renderer);

	map->Draw();
	manager.Draw();
	SDL_RenderPresent(renderer);
}

void Game::Clean() 
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}