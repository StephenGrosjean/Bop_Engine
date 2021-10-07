#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "TileMap.h"
#include "ECS.h"
#include "Components.h"

GameObject* player;
SDL_Renderer* Game::renderer = nullptr;
TileMap* map;
Manager manager;
auto& newPlayer(manager.AddEntity());

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

	player = new GameObject("Assets/player.png", 0, 0);
	map = new TileMap();

	newPlayer.AddComponent<PositionComponent>();
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
	player->Update();
	manager.Update();
	std::cout << newPlayer.GetComponent<PositionComponent>().x() << "," <<
		newPlayer.GetComponent<PositionComponent>().y() << std::endl;
}

void Game::Render() 
{
	SDL_RenderClear(renderer);

	map->Draw();
	player->Render();

	SDL_RenderPresent(renderer);
}

void Game::Clean() 
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;
}