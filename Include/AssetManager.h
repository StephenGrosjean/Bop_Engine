#pragma once
#include <map>
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
#include "ECS\ECS.h"
#include "SDL_ttf.h"
#include <SDL_mixer.h>

class AssetManager
{
public:
	AssetManager(Manager* manager);

	~AssetManager();


	//GameObjects
	void CreateProjectile(Vec2i position, Vec2f velocity, std::string textureId);

	//Texture Management
	void AddTexture(std::string id, const char* path);
	SDL_Texture* GetTexture(std::string id);

	//Font Management
	void AddFont(std::string id, std::string path, int fontSize);
	TTF_Font* GetFont(std::string id);

	//Sound Management
	void AddMusic(std::string id, std::string path);
	void AddSFX(std::string id, std::string path);
	Mix_Music* GetMusic(std::string id);
	Mix_Chunk* GetSFX(std::string id);

private:
	Manager* manager;
	std::map<std::string, SDL_Texture*> textures;
	std::map<std::string, TTF_Font*> fonts;
	std::map<std::string, Mix_Music*> music;
	std::map<std::string, Mix_Chunk*> sfx;
};