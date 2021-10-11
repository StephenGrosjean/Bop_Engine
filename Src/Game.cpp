#include "..\Game.h"
#include "..\TextureManager.h"
#include "..\TileMap.h"
#include "..\ECS\Components.h"
#include "..\Vector2D.h"
#include "..\Collision.h"

#include <sstream>

TileMap* map;
Manager manager;
SDL_Event Game::event;
SDL_Renderer* Game::renderer = nullptr;
AssetManager* Game::assetManager = new AssetManager(&manager);
InputManager* Game::inputManager = new InputManager();

SDL_Rect Game::camera = { 0, 0, 800, 640};

auto& player1(manager.AddEntity());
auto& player2(manager.AddEntity());
auto& validTile(manager.AddEntity());



auto& label(manager.AddEntity());

auto& tiles(manager.GetGroup(Game::groupMap));
auto& players(manager.GetGroup(Game::groupPlayers));
auto& colliders(manager.GetGroup(Game::groupColliders));
auto& projectiles(manager.GetGroup(Game::groupProjectiles));
auto& validTiles(manager.GetGroup(Game::groupValidTiles));

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
	assetManager->AddTexture("validTile", "Assets/validTile.png");
	assetManager->AddTexture("collider", "Assets/ColliderTexture.png");
	assetManager->AddFont("arial", "Assets/Fonts/arial.ttf", 16);

	map = new TileMap("terrain", 2, 32);

	map->Load("Assets/map.map", Vec2i(10, 10));
	map->SetTileTexture(Vec2i(64, 64), "validTile");

	validTile.AddComponent<TransformComponent>(500,500, 32, 32, 2);
	validTile.AddComponent<SpriteComponent>("collider", false);
	validTile.AddComponent<ColliderComponent>();
	validTile.GetComponent<ColliderComponent>().collider = { 500,500 };
	validTile.AddComponent<ValidTileComponent>();
	validTile.AddGroup(groupValidTiles);

	player1.AddComponent<TransformComponent>(3);
	player1.GetComponent<TransformComponent>().position = Vec2f(200, 200);
	player1.AddComponent<SpriteComponent>("player", true);
	player1.AddComponent<KeyboardController>(0);
	player1.AddComponent<ColliderComponent>();
	player1.GetComponent<ColliderComponent>().collider = { 200,200 };
	player1.AddGroup(groupPlayers);

	player2.AddComponent<TransformComponent>(3);
	player2.GetComponent<TransformComponent>().position = Vec2f(400, 400);
	player2.AddComponent<SpriteComponent>("player", true);
	player2.AddComponent<KeyboardController>(1);
	player2.AddComponent<ColliderComponent>();
	player2.GetComponent<ColliderComponent>().collider = { 400,400 };
	player2.AddGroup(groupPlayers);

	assetManager->CreateProjectile(Vec2i(600, 0), Vec2f::left, 200, 2, "projectile");

	SDL_Color white = { 255,255,255,255 };
	label.AddComponent<UILabel>(Vec2i(10,10), "Test string", "arial", white);
	
}

void Game::HandleEvents()
{
	
	inputManager->Update();

	if (inputManager->isQuit)
	{
		Game::SetRunning(false);
	}
}

void Game::Update()
{
	ColliderComponent& player1Col = player1.GetComponent<ColliderComponent>();
	ColliderComponent& player2Col = player2.GetComponent<ColliderComponent>();
	Vec2f player1Vel = player1.GetComponent<TransformComponent>().velocity;
	Vec2f player2Vel = player2.GetComponent<TransformComponent>().velocity;

	Vec2f player1Pos = player1.GetComponent<TransformComponent>().position;
	Vec2f player2Pos = player2.GetComponent<TransformComponent>().position;

	std::stringstream ss;
	ss << "Player position : " << player1Pos;
	label.GetComponent<UILabel>().SetLabelText(ss.str(), "arial");

	manager.Refresh();
	manager.Update();

	for (auto& c : colliders)
	{
		ColliderComponent& cCol = c->GetComponent<ColliderComponent>();
		if (Collision::AABB(cCol, player1Col))
		{
			player1.GetComponent<TransformComponent>().position = player1Pos;
			//player1.GetComponent<TransformComponent>().velocity = player1Vel * -1;
		}

		if (Collision::AABB(cCol, player2Col))
		{
			player2.GetComponent<TransformComponent>().position = player2Pos;
			//player2.GetComponent<TransformComponent>().velocity = player2Vel * -1;
		}
	}

	for (auto& p : projectiles)
	{
		if (Collision::AABB(player1.GetComponent<ColliderComponent>().collider, p->GetComponent<ColliderComponent>().collider))
		{
			p->Destroy();
		}
	}

	for (auto& v : validTiles)
	{
		ColliderComponent& cCol = v->GetComponent<ColliderComponent>();
		if (Collision::AABB(cCol, player1Col))
		{
			std::cout << "Player 1 is in validPos" << std::endl;
		}
		if (Collision::AABB(cCol, player2Col))
		{
			std::cout << "Player 2 is in validPos" << std::endl;
		}
	}

	/*camera.x = player1.GetComponent<TransformComponent>().position.x - 400;
	camera.y = player1.GetComponent<TransformComponent>().position.y - 320;

	if (camera.x < 0)
		camera.x = 0;

	if (camera.y < 0)
		camera.y = 0;

	if (camera.x > camera.w)
		camera.x = camera.w;

	if (camera.y > camera.h)
		camera.y = camera.h;*/
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

	for (auto& v : validTiles)
	{
		v->Draw();
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

void Game::SetRunning(bool value)
{
	isRunning = value;
}

bool Game::GetRunning()
{
	return isRunning;
}

