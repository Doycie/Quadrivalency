#pragma once
#include <glm\glm.hpp>
#include <vector>
#include "SpriteBatch.h"
#include "TextureCache.h"

#include "Tile.h"




class Ship
{
public:
	Ship();
	Ship(TextureCache texCache);
	~Ship();

	void draw(SpriteBatch& spriteBatch);
	void update();
	void addTile(char floorType, TextureCache texCache, glm::vec2 coords);

private:

	std::vector<Tile>* _tiles = new std::vector<Tile>;



};

