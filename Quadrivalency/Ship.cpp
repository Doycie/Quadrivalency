#include "Ship.h"



Ship::Ship()
{
}


Ship::~Ship()
{
}

void Ship::addTile(char floorType, TextureCache texCache,glm::vec2 coords)
{
	int x = coords.x / 64;
	int y = coords.y / 64;

	Tile t(floorType,texCache, x, y);
	_tiles.push_back(t);
}

void Ship::update() {

}

void Ship::draw(SpriteBatch &spriteBatch) {
	
	
	for (int i = 0; i < _tiles.size(); i++) {

		_tiles[i].draw(spriteBatch);

	}


}