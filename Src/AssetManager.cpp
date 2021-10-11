#include "..\AssetManager.h"
#include "..\ECS\Components.h"

AssetManager::AssetManager(Manager* manager) : manager(manager)
{
}

AssetManager::~AssetManager()
{
}

void AssetManager::CreateProjectile(Vec2i position, Vec2f velocity, int range, int speed, std::string textureId)
{
	auto& projectile(manager->AddEntity());
	projectile.AddComponent<TransformComponent>(position.x, position.y, 32, 32, 1);
	projectile.AddComponent<SpriteComponent>(textureId, false);
	projectile.AddComponent<ProjectileComponent>(range, speed, velocity);
	projectile.AddComponent<ColliderComponent>("Projectile");
	projectile.AddGroup(Game::groupProjectiles);
}

void AssetManager::AddTexture(std::string id, const char* path)
{
	textures.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture* AssetManager::GetTexture(std::string id)
{
	return textures[id];
}

void AssetManager::AddFont(std::string id, std::string path, int fontSize)
{
	fonts.emplace(id, TTF_OpenFont(path.c_str(), fontSize));
}

TTF_Font* AssetManager::GetFont(std::string id)
{
	return fonts[id];
}
