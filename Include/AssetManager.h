#pragma once
#include <map>
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
#include "ECS\ECS.h"

class AssetManager
{
public:
	AssetManager(Manager* manager);

	~AssetManager();

	void AddTexture(std::string id, const char* path);
	SDL_Texture* GetTexture(std::string id);


private:
	Manager* manager;
	std::map<std::string, SDL_Texture*> textures;
};