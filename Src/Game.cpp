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
AssetManager* Game::assetManager = new AssetManager(&manager);

SDL_Rect Game::camera = { 0,0,800,640};

auto& player(manager.AddEntity());

auto& tiles(manager.GetGroup(Game::groupMap));
auto& players(manager.GetGroup(Game::groupPlayers));
auto& colliders(manager.GetGroup(Game::groupColliders));

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

	assetManager->AddTexture("terrain", "Assets/terrain_ss.png");
	assetManager->AddTexture("player", "Assets/player_anims.png");

	map = new TileMap("terrain", 2, 32);

	map->Load("Assets/map.map", Vec2i(10, 10));

	player.AddComponent<TransformComponent>(3);
	player.GetComponent<TransformComponent>().position = Vec2f(200, 200);
	player.AddComponent<SpriteComponent>("player", true);
	player.AddComponent<KeyboardController>();
	player.AddComponent<ColliderComponent>();
	player.GetComponent<ColliderComponent>().collider = { 200,200 };
	player.AddGroup(groupPlayers);
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
	SDL_Rect playerCol = player.GetComponent<ColliderComponent>().collider;
	Vec2f playerPos = player.GetComponent<TransformComponent>().position;

	manager.Refresh();
	manager.Update();

	for (auto& c : colliders)
	{
		SDL_Rect cCol = c->GetComponent<ColliderComponent>().collider;
		if (Collision::AABB(cCol, playerCol))
		{
			std::cout << player.GetComponent<TransformComponent>().position << std::endl;
			player.GetComponent<TransformComponent>().position = playerPos;
		}
	}

	camera.x = player.GetComponent<TransformComponent>().position.x - 400;
	camera.y = player.GetComponent<TransformComponent>().position.y - 320;

	if (camera.x < 0)
		camera.x = 0;

	if (camera.y < 0)
		camera.y = 0;

	if (camera.x > camera.w)
		camera.x = camera.w;

	if (camera.y > camera.h)
		camera.y = camera.h;
}

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

	for (auto& c : colliders)
	{
		c->Draw();
	}

	SDL_RenderPresent(renderer);
}

void Game::Clean() 
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

