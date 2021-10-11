#pragma once
#include "..\ECS\ECS.h"
#include "SDL.h"
#include "..\Vector2D.h"

class ValidTileComponent : public Component
{
public:
	ValidTileComponent() {}
	
	void SetTilePos(Entity& tileEntity, Vec2i position)
	{
		lastEntity = &tileEntity;
		tileEntity.GetComponent<TileComponent>().SetTexture("validTexture");
		entity->GetComponent<TransformComponent>().position = Vec2f(position.x, position.y);
	}

	void DisableTile()
	{
		entity->GetComponent<TransformComponent>().position = Vec2f(1000,1000);

	}

private:
	Entity* lastEntity;
};

