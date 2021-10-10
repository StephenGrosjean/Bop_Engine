#pragma once
#include "Vector2D.h"
#include <string>
class TileMap
{
public:
	TileMap(std::string textureID, int mapScale, int tileSize);
	~TileMap();

	void Load(std::string path, Vec2i size);
	void AddTile(Vec2i sourceCoords, Vec2i position);

private:
	std::string textureID;
	int mapScale;
	int tileSize;

};