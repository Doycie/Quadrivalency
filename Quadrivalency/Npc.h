#pragma once
#include "SpriteBatch.h"
#include "TextureCache.h"
#include "Tile.h"
#include "Node.h"
#include "PathFinder.h"
#include "Utility.h"
#include <math.h>
#include <list>    


class Npc
{
public:
	Npc(TextureCache texCache);
	~Npc();

	void update();
	void draw(SpriteBatch &spriteBatch);

	void setPath(int x, Tile tiles[1024]);

	int getTile();

private:
	int movementSpeed = 5;

	int _xTile;
	
	int _x;
	int _y;

	std::vector<int> path;

	GLuint _tex;
	float _angle;

	
};

