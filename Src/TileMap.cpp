#include "TileMap.h"
#include "Game.h"
#include <fstream>

TileMap::TileMap()
{
}

TileMap::~TileMap()
{
}

void TileMap::Load(std::string path, Vec2i size)
{
	char tile;
	std::fstream mapFile;
	mapFile.open(path);

	for (int y = 0; y < size.y; y++)
	{
		for (int x = 0; x < size.x; x++)
		{
			mapFile.get(tile);
			Game::AddTile(atoi(&tile), Vec2i(x * 32, y * 32));
			mapFile.ignore();
		}
	}

	mapFile.close();
}
