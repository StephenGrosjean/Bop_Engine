#pragma once
#include "Vector2D.h"
#include <string>
class TileMap
{
public:
	TileMap();
	~TileMap();

	static void Load(std::string path, Vec2i size);

private:

};