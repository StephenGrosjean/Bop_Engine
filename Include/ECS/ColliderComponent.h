#pragma once
#include <string>
#include "SDL.h"
#include "Components.h"
#include "..\TextureManager.h"


/// <summary>
/// Coomponent used to create a collider
/// </summary>
class ColliderComponent : public Component
{
public:
	enum class Type
	{
		Box,
		Sphere
	};

	TransformComponent* transform;  // Entity transform component

	SDL_Rect collider;				// Collider rect
	std::string tag;				// Collider tag

	SDL_Texture* texture;			// Collider texture (used to visualize colliders)
	SDL_Rect srcRect;				// Source rect of the texture
	SDL_Rect destRect;				// Destination rect of the texture
	int radius;
	Type type;
	Vec2f scale = Vec2f::one;

	//Default constructor
	ColliderComponent()
	{
		tag = "Default";
	}

	/// <summary>
	/// Create Collider component with a tag
	/// </summary>
	/// <param name="tag">: Tag of the collider</param>
	ColliderComponent(const std::string& tag)
	{
		this->tag = tag;
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="tag">: Tag of the collider</param>
	/// <param name="position">: Position of the collider</param>
	/// <param name="size">: Size of the collider</param>
	ColliderComponent(const std::string& tag, const Vec2i& position, int size)
	{
		this->tag = tag;
		collider.x = position.x;
		collider.y = position.y;
		collider.h = collider.w = size;
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="tag">: Tag of the collider</param>
	/// <param name="position">: Position of the collider</param>
	/// <param name="size">: Size of the collider</param>
	ColliderComponent(const std::string& tag, const Vec2i& position, const Vec2f& scale)
	{
		this->tag = tag;
		collider.x = position.x;
		collider.y = position.y;
		this->scale = scale;
	}

	void SetPosition(Vec2i pos)
	{
		collider.x = pos.x;
		collider.y = pos.y;
	}

	//Called on the start of the component
	void Init() override
	{
		//Add the TransformComponent if not present
		if (!entity->HasComponent<TransformComponent>())
		{
			entity->AddComponent<TransformComponent>();
		}
		transform = &entity->GetComponent<TransformComponent>();

		//Load the collider texture and set the src and dest Rects
		texture = TextureManager::LoadTexture("Assets/ColliderTexture.png");
		srcRect = { 0,0,32,32 };
		destRect = { collider.x, collider.y, collider.w, collider.h };
	}
	
	//Called every frame
	void Update() override
	{
		//Move the colliders depending on the transform position if not a terrain
		if (tag != "Terrain")
		{
			collider.x = static_cast<int>(transform->position.x);
			collider.y = static_cast<int>(transform->position.y);
			collider.w = transform->width * transform->scale.x * scale.x;
			collider.h = transform->height * transform->scale.y * scale.y;
		}
		
		destRect.x = collider.x - Game::camera.x;
		destRect.y = collider.y - Game::camera.y;
	}

	//Called every draw frame
	void Draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
	}
};