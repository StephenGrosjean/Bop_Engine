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
auto& validTile1(manager.AddEntity());
auto& validTile2(manager.AddEntity());
auto& validTile3(manager.AddEntity());
auto& validTile4(manager.AddEntity());

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
	assetManager->AddTexture("player1", "Assets/player1_anims.png");
	assetManager->AddTexture("player2", "Assets/player2_anims.png");
	assetManager->AddTexture("projectile", "Assets/projectile.png");
	assetManager->AddTexture("validTile", "Assets/validTile.png");
	assetManager->AddTexture("collider", "Assets/ColliderTexture.png");
	assetManager->AddFont("arial", "Assets/Fonts/arial.ttf", 16);

	map = new TileMap("terrain", 2, 32);

	map->Load("Assets/map.map", Vec2i(10, 10));
	//map->SetTileTexture(Vec2i(64, 64), "validTile");

	CreateValidTiles();

	player1.AddComponent<TransformComponent>(1);
	player1.GetComponent<TransformComponent>().position = Vec2f(200, 200);
	player1.AddComponent<SpriteComponent>("player1", true);
	player1.AddComponent<KeyboardController>(0);
	player1.AddComponent<ColliderComponent>("Player1", Vec2i(200,200), Vec2f(1,0.5f));
	player1.AddGroup(groupPlayers);

	player2.AddComponent<TransformComponent>(1);
	player2.GetComponent<TransformComponent>().position = Vec2f(400, 400);
	player2.AddComponent<SpriteComponent>("player2", true);
	player2.AddComponent<KeyboardController>(1);
	player2.AddComponent<ColliderComponent>();
	player2.GetComponent<ColliderComponent>().collider = { 400,400 };
	player2.AddGroup(groupPlayers);

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
	timer += deltaTime;
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
			player1.GetComponent<TransformComponent>().position = player1Pos +(player1Vel * -0.1f);
			//player1.GetComponent<TransformComponent>().velocity = ;
		}

		if (Collision::AABB(cCol, player2Col))
		{
			player2.GetComponent<TransformComponent>().position = player2Pos + (player2Vel * -0.1f);
			//player2.GetComponent<TransformComponent>().velocity = player2Vel * -1;
		}
	}

	for (auto& p : projectiles)
	{
		if (!isPlayer1Valid)
		{
			if (Collision::AABB(player1.GetComponent<ColliderComponent>().collider, p->GetComponent<ColliderComponent>().collider))
			{
				std::cout << "P1 DEAD" << std::endl;
				//player1.Destroy();
			}
		}

		if (!isPlayer2Valid)
		{
			if (Collision::AABB(player2.GetComponent<ColliderComponent>().collider, p->GetComponent<ColliderComponent>().collider))
			{
				std::cout << "P2 DEAD" << std::endl;
				//player2.Destroy();
			}
		}
	}

	bool tmpP1Valid = false;
	bool tmpP2Valid = false;
	for (auto& v : validTiles)
	{
		ColliderComponent& cCol = v->GetComponent<ColliderComponent>();

		if (Collision::AABB(cCol, player1Col))
		{
			tmpP1Valid = true;
		}
		if (Collision::AABB(cCol, player2Col))
		{
			tmpP2Valid = true;
		}
	}

	isPlayer1Valid = tmpP1Valid;
	isPlayer2Valid = tmpP2Valid;

	if (timer > 200 && !hasPlacedTiles)
	{
		hasPlacedTiles = true;
		SetRandomTiles();
	}

	if (timer > 500)
	{
		SpawnLaser();
		hasPlacedTiles = false;
		timer = 0;
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

	for (auto& v : validTiles)
	{
		v->Draw();
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

void Game::SetRunning(bool value)
{
	isRunning = value;
}

bool Game::GetRunning()
{
	return isRunning;
}

void Game::SetDeltaTime(float time)
{
	deltaTime = time;
}

void Game::SpawnLaser()
{
	assetManager->CreateProjectile(Vec2i(600, 0), Vec2f::left, 500, 2, "projectile");
}

void Game::SetRandomTiles()
{
	Vec2f rdmPos1 = Vec2f((std::rand() % 8) + 1, (std::rand() % 8) + 1) * 64;
	Vec2f rdmPos2 = Vec2f((std::rand() % 8) + 1, (std::rand() % 8) + 1) * 64;
	Vec2f rdmPos3 = Vec2f((std::rand() % 8) + 1, (std::rand() % 8) + 1) * 64;
	Vec2f rdmPos4 = Vec2f((std::rand() % 8) + 1, (std::rand() % 8) + 1) * 64;

	std::cout << rdmPos1 << std::endl;
	std::cout << rdmPos2 << std::endl;
	std::cout << rdmPos3 << std::endl;
	std::cout << rdmPos4 << std::endl;

	validTile1.GetComponent<TransformComponent>().position = rdmPos1;
	validTile2.GetComponent<TransformComponent>().position = rdmPos2;
	validTile3.GetComponent<TransformComponent>().position = rdmPos3;
	validTile4.GetComponent<TransformComponent>().position = rdmPos4;
}

void Game::CreateValidTiles()
{
	validTile1.AddComponent<TransformComponent>(1000, 1000, 32, 32, 2);
	validTile2.AddComponent<TransformComponent>(1000, 1000, 32, 32, 2);
	validTile3.AddComponent<TransformComponent>(1000, 1000, 32, 32, 2);
	validTile4.AddComponent<TransformComponent>(1000, 1000, 32, 32, 2);

	validTile1.AddComponent<SpriteComponent>("validTile", false);
	validTile2.AddComponent<SpriteComponent>("validTile", false);
	validTile3.AddComponent<SpriteComponent>("validTile", false);
	validTile4.AddComponent<SpriteComponent>("validTile", false);

	validTile1.AddComponent<ColliderComponent>();
	validTile2.AddComponent<ColliderComponent>();
	validTile3.AddComponent<ColliderComponent>();
	validTile4.AddComponent<ColliderComponent>();

	validTile1.GetComponent<ColliderComponent>().collider = { 1000, 1000 };
	validTile2.GetComponent<ColliderComponent>().collider = { 1000, 1000 };
	validTile3.GetComponent<ColliderComponent>().collider = { 1000, 1000 };
	validTile4.GetComponent<ColliderComponent>().collider = { 1000, 1000 };

	validTile1.AddComponent<ValidTileComponent>();
	validTile2.AddComponent<ValidTileComponent>();
	validTile3.AddComponent<ValidTileComponent>();
	validTile4.AddComponent<ValidTileComponent>();

	validTile1.AddGroup(groupValidTiles);
	validTile2.AddGroup(groupValidTiles);
	validTile3.AddGroup(groupValidTiles);
	validTile4.AddGroup(groupValidTiles);
}

