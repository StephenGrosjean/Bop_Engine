#pragma once
#include "Vector2D.h"
#include <map>
#include <string>
#include <vector>
class Entity;
class TileComponent;

class TileMap
{
public:
	TileMap(std::string textureID, int mapScale, int tileSize);
	~TileMap();

	class Tile
	{
	public:
		Tile(Vec2i pos, Entity& entity) : pos(pos), entity(entity) {}
		Vec2i pos;
		Entity& entity;
	};

	void Load(std::string path, Vec2i size);
	void AddTile(Vec2i sourceCoords, Vec2i position);
	void SetTileTexture(Vec2i position, std::string textureID);
	Entity& GetTileEntity(Vec2i position);

private:
	std::string textureID;
	int mapScale;
	int tileSize;
	std::vector<Tile> tiles;

};