#ifndef Game_h
#define Game_h
#include "SDL.h"
#include <iostream>
#include <vector>
#include "Vector2D.h"
#include "SDL_image.h"
#include "AssetManager.h"
#include "InputManager.h"
#include "DifficultyManager.h"
#include "Time.h"

class ColliderComponent;
class AudioManager;

class Game {

public:
	Game();
	~Game();

	void Init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);
	
	void HandleEvents();
	void Update();
	void Render();
	void Clean();
	
	void SetRunning(bool value);
	bool GetRunning();

	void SpawnLaser();
	void SetRandomTiles();
	void CreateValidTiles();

	static SDL_Renderer* renderer;
	static SDL_Event event;
	static SDL_Rect camera;
	static AssetManager* assetManager;
	static InputManager* inputManager;
	static AudioManager* audioManager;
	static DifficultyManager* difficultyManager;
	static Time* time;

	enum groupLabels : std::size_t
	{
		groupMap,
		groupPlayers,
		groupEnemies,
		groupColliders,
		groupProjectiles,
		groupValidTiles
	};


private:
	bool hasPlacedTiles = false;
	bool isRunning = false;
	int counter = 0;
	SDL_Window* window;
	bool isPlayer1Valid;
	bool isPlayer2Valid;
	bool isPlayer1Dead;
	bool isPlayer2Dead;
	float timer;
	bool hasSpawnedLaser = false;
	bool startPressed = false;
	bool gameOver = false;
	int levelCounter = 1;


	//sound check
	bool isDeathSoundPlayed = false;
	bool hasPlayedWarningSound = false;
	bool hasPlayedStartSound = false;
};



#endif /* Game_h */
