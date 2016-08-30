#pragma once
#include <glm\glm.hpp>
#include <vector>
#include "SpriteBatch.h"
#include "TextureCache.h"

#include "Tile.h"
#include "Npc.h"



class Ship
{
public:
	Ship();
	Ship(TextureCache texCache);
	~Ship();

	void draw(SpriteBatch& spriteBatch);
	void update();
	void addTile(char floorType, TextureCache texCache, int x);

private:

	Tile tiles[1024];
	std::vector<Npc> npcs;

};

