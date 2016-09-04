#pragma once
#include "SpriteBatch.h"
#include "TextureCache.h"
#include "Tile.h"
#include "Node.h"
#include "PathFinder.h"
#include <list>    


class Npc
{
public:
	Npc(TextureCache texCache);
	~Npc();

	void update(Tile tiles[1024]);
	void draw(SpriteBatch &spriteBatch);

	void setTargetTile(int x);

private:

	int _xTile;
	
	int _x;
	int _y;

	std::vector<int> path;

	GLuint _tex;
	float _angle;

	
};

