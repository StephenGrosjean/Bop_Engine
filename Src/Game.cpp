#include "Game.h"
#include "TextureManager.h"
#include "TileMap.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"

TileMap* map;
Manager manager;
SDL_Event Game::event;
SDL_Renderer* Game::renderer = nullptr;

std::vector<ColliderComponent*> Game::colliders;

auto& player(manager.AddEntity());
auto& wall(manager.AddEntity());

enum groupLabels : std::size_t
{
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders
};

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

	TileMap::Load("Assets/map.map", Vec2i(16, 16));

	player.AddComponent<TransformComponent>(2);
	player.AddComponent<SpriteComponent>("Assets/player_anims.png", true);
	player.AddComponent<KeyboardController>();
	player.AddComponent<ColliderComponent>();
	player.AddGroup(groupPlayers);

	wall.AddComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
	wall.AddComponent<SpriteComponent>("Assets/dirt.png");
	wall.AddComponent<ColliderComponent>("wall");
	wall.AddGroup(groupMap);
}

void Game::HandleEvents()
{
	
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

	for (auto c : colliders)
	{
		Collision::AABB(player.GetComponent<ColliderComponent>(), *c);
	}

	
}

auto& tiles(manager.GetGroup(groupMap));
auto& players(manager.GetGroup(groupPlayers));
auto& enemies(manager.GetGroup(groupEnemies));

void Game::Render() 
{
	SDL_RenderClear(renderer);

	for (auto& t : tiles)
	{
		t->Draw();
	}

	for (auto& p : players)
	{
		p->Draw();
	}

	for (auto& e : enemies)
	{
		e->Draw();
	}

	SDL_RenderPresent(renderer);
}

void Game::Clean() 
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void Game::AddTile(int id, Vec2i position)
{
	auto& tile(manager.AddEntity());
	tile.AddComponent<TileComponent>(position, Vec2i(32, 32), id);
	tile.AddGroup(groupMap);

}
