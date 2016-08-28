#include "Ship.h"



Ship::Ship()
{
}

Ship::Ship(TextureCache texCache)
{
	_tiles.reserve(10);
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
	
	Pos tilePos(x, y);

	//std::vector<Tile>::iterator it = _tiles.begin();
	//while ( it != _tiles.end()) {
	//	if (tilePos == it->_pos) {
	//		it = _tiles.erase(it);
	//		empty = false;
	//	}
	//	else {
	//		it++;
	//	}
	//}

	for (int i = 0; i < _tiles.size(); i++) {
		if (tilePos == _tiles[i]._pos) {
			_tiles[i].removeForNeighbours(_tiles);
			_tiles.erase(_tiles.begin() + i);

			empty = false;
		}
	}


	if (empty) {
		_tiles.push_back(Tile(floorType,texCache,_tiles,tilePos));
		//_tiles.insert(std::pair < TilePos, TileClass>(TilePos(x, y),  TileClass(floorType, texCache, _tiles, x, y)));
	}

}


void Ship::update() {

}

void Ship::draw(SpriteBatch &spriteBatch) {
	
	for (auto it = _tiles.begin(); it != _tiles.end(); it++) {
		it->draw(spriteBatch, it->_pos.x,it->_pos.y);
	}
	

}