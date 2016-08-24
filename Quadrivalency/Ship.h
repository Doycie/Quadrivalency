#pragma once
#include <glm\glm.hpp>
#include <vector>
#include "SpriteBatch.h"
#include "TextureCache.h"

#include "TileClass.h"

struct ComparatorIs {
	bool operator()(const TilePos& t, const TilePos& v) const {
		if (t._x == v._x && t._y == v._y)
			return true;
		return false;
	}
};

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

	std::map < TilePos, TileClass  > _tiles;



};

