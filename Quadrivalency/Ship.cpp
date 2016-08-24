#include "Ship.h"



Ship::Ship()
{
}

Ship::Ship(TextureCache texCache)
{
	addTile(1, texCache, glm::vec2(512, 512));
}


Ship::~Ship()
{
}

void Ship::addTile(char floorType, TextureCache texCache, glm::vec2 coords)
{
	int x = (int) (coords.x) / 64;
	int y = (int) (coords.y) / 64;
	if (x < 0)
		x -= 1;
	if (y < 0)
		y -=1;

	bool empty = true;
	TilePos a(x, y);
	if (_tiles.count(a)>0) {
		_tiles.erase(a);
		empty = false;
	}

	if (empty) {
		
		_tiles.insert(std::pair < TilePos, TileClass>(TilePos(x, y),  TileClass(floorType, texCache, _tiles, x, y)));
		
	}

}


void Ship::update() {

}

void Ship::draw(SpriteBatch &spriteBatch) {
	
	for (std::map<TilePos, TileClass>::iterator it = _tiles.begin(); it != _tiles.end(); it++) {
		it->second.draw(spriteBatch, it->first._x,it->first._y);
	}
	

}