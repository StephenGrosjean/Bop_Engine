#include "AssetManager.h"

AssetManager::AssetManager(Manager* manager) : manager(manager)
{
}

AssetManager::~AssetManager()
{
}

void AssetManager::AddTexture(std::string id, const char* path)
{
	textures.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture* AssetManager::GetTexture(std::string id)
{
	return textures[id];
}
