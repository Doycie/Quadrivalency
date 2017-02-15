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

	~Ship();

	void init(TextureCache texCache);

	void draw(SpriteBatch& spriteBatch);
	void update();
	void addTile(char floorType, TextureCache texCache, int x);

	std::vector<Npc> npcs;

	Tile tiles[1024];

private:
};
