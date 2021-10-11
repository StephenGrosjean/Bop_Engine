#include "..\TileMap.h"
#include "..\Game.h"
#include <fstream>
#include "..\ECS\ECS.h"
#include "..\ECS\Components.h"
#include "..\Game.h"

extern Manager manager;

TileMap::TileMap(std::string textureID, int mapScale, int tileSize)
	: textureID(textureID), mapScale(mapScale), tileSize(tileSize)
{
}

TileMap::~TileMap()
{
}

void TileMap::Load(std::string path, Vec2i size)
{
	char c;
	std::fstream mapFile;
	mapFile.open(path);

	Vec2i sourceCoords;

	for (int y = 0; y < size.y; y++)
	{
		for (int x = 0; x < size.x; x++)
		{
			mapFile.get(c);
			sourceCoords.y = atoi(&c) * tileSize;
			mapFile.get(c);
			sourceCoords.x = atoi(&c) * tileSize;

			AddTile(sourceCoords, Vec2i(x, y) * (tileSize* mapScale));
			mapFile.ignore();
		}
	}

	mapFile.ignore();

	for (int y = 0; y < size.y; y++)
	{
		for (int x = 0; x < size.x; x++)
		{
			mapFile.get(c);
			if (c == '1')
			{
				auto& tcol(manager.AddEntity());
				tcol.AddComponent<ColliderComponent>("Terrain", Vec2i(x,y) * (tileSize * mapScale), tileSize * mapScale);
				tcol.AddGroup(Game::groupColliders);
			}
			mapFile.ignore();
		}
	}

	mapFile.close();
}

void TileMap::AddTile(Vec2i sourceCoords, Vec2i position)
{
	auto& tile(manager.AddEntity());
	tile.AddComponent<TileComponent>(sourceCoords, position, tileSize, mapScale, textureID);	
	tile.AddGroup(Game::groupMap);
	Tile t(position, tile);
	tiles.push_back(t);
}

void TileMap::SetTileTexture(Vec2i position, std::string textureID)
{
	for (auto& t : tiles)
	{
		if (t.pos == position)
		{
			t.entity.GetComponent<TileComponent>().SetTexture(textureID);
		}
	}
}

Entity& TileMap::GetTileEntity(Vec2i position)
{
	for (auto& t : tiles)
	{
		if (t.pos == position)
		{
			return t.entity;
		}
	}
}
