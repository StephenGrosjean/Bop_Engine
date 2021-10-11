#include "Game.h"
#include "TextureManager.h"
#include "TileMap.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"

#include <sstream>

TileMap* map;
Manager manager;
SDL_Event Game::event;
SDL_Renderer* Game::renderer = nullptr;
AssetManager* Game::assetManager = new AssetManager(&manager);
InputManager* Game::inputManager = new InputManager();

SDL_Rect Game::camera = { 0,0,800,640};

auto& player(manager.AddEntity());
auto& label(manager.AddEntity());

auto& tiles(manager.GetGroup(Game::groupMap));
auto& players(manager.GetGroup(Game::groupPlayers));
auto& colliders(manager.GetGroup(Game::groupColliders));
auto& projectiles(manager.GetGroup(Game::groupProjectiles));

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

	if (TTF_Init() == -1)
	{
		std::cout << "Error SDL_TTF" << std::endl;
	}

	assetManager->AddTexture("terrain", "Assets/terrain_ss.png");
	assetManager->AddTexture("player", "Assets/player_anims.png");
	assetManager->AddTexture("projectile", "Assets/projectile.png");
	assetManager->AddFont("arial", "Assets/Fonts/arial.ttf", 16);

	map = new TileMap("terrain", 2, 32);

	map->Load("Assets/map.map", Vec2i(10, 10));

	player.AddComponent<TransformComponent>(3);
	player.GetComponent<TransformComponent>().position = Vec2f(200, 200);
	player.AddComponent<SpriteComponent>("player", true);
	player.AddComponent<KeyboardController>();
	player.AddComponent<ColliderComponent>();
	player.GetComponent<ColliderComponent>().collider = { 200,200 };
	player.AddGroup(groupPlayers);

	//assetManager->CreateProjectile(Vec2i(400, 100), Vec2f::left, 200, 2, "projectile");

	SDL_Color white = { 255,255,255,255 };
	label.AddComponent<UILabel>(Vec2i(10,10), "Test string", "arial", white);
}

void Game::HandleEvents()
{
	
	inputManager->Update();
	
	/*switch (event.type)
	{
		case SDL_QUIT:
			isRunning = false;
			break;
		default:
			break;
	}*/
}

void Game::Update()
{
	SDL_Rect playerCol = player.GetComponent<ColliderComponent>().collider;
	Vec2f playerPos = player.GetComponent<TransformComponent>().position;

	std::stringstream ss;
	ss << "Player position : " << playerPos;
	label.GetComponent<UILabel>().SetLabelText(ss.str(), "arial");

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

	for (auto& p : projectiles)
	{
		if (Collision::AABB(player.GetComponent<ColliderComponent>().collider, p->GetComponent<ColliderComponent>().collider))
		{
			p->Destroy();
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

	for (auto& p : projectiles)
	{
		p->Draw();
	}

	label.Draw();

	SDL_RenderPresent(renderer);
	inputManager->Reset();
}

void Game::Clean() 
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

