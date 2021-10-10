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
	char c;
	std::fstream mapFile;
	mapFile.open(path);

	Vec2i sourceCoords;

	for (int y = 0; y < size.y; y++)
	{
		for (int x = 0; x < size.x; x++)
		{
			mapFile.get(c);
			sourceCoords.y = atoi(&c) * 32;
			mapFile.get(c);
			sourceCoords.x = atoi(&c) * 32;

			Game::AddTile(sourceCoords, Vec2i(x, y)*64);
			mapFile.ignore();
		}
	}

	mapFile.close();
}
