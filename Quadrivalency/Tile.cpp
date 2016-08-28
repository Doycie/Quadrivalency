#include "Tile.h"


Tile::Tile(char floorType, TextureCache texCache, std::vector<Tile>* tiles, Pos position) {
	_floor._type = floorType;
	_pos = position;
	updateNeighbours(tiles);
	if (floorType == 1) {
		updateTileTex(texCache,tiles);
	}
	for (int i = 0; i < 4; i++) {
		if (hasNeighbour[i]) {
			neighbours[i]->updateNeighbours(tiles);
			neighbours[i]->updateTileTex(texCache, tiles);
		}
	}
}

void Tile::draw(SpriteBatch &spriteBatch, int x, int y) {
	int TiSi = 64;
	spriteBatch.draw(glm::vec4(x * TiSi, y*TiSi, TiSi, TiSi), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), _floor._tex, 0.0f, ColorRGBA8(255, 255, 255, 5), 0.0f);
}


void Tile::updateNeighbours(std::vector<Tile>* tiles) {
	
	for (int i = 0; i <4; i++) {
		hasNeighbour[i] = false;
	}
	Pos left(_pos.x - 1, _pos.y);
	Pos right(_pos.x + 1, _pos.y);
	Pos bot(_pos.x, _pos.y - 1);
	Pos top(_pos.x, _pos.y + 1);

	for (unsigned int i = 0; i < tiles->size(); i++) {
		Pos tilePos = tiles->at(i)._pos;

		if (tilePos == left) {
			neighbours[0] = &tiles->at(i);
			hasNeighbour[0] = true;
		}
		if (tilePos == top) {
			neighbours[1] = &tiles->at(i);
			hasNeighbour[1] = true;
		}
		if (tilePos == right) {
			neighbours[2] = &tiles->at(i);
			hasNeighbour[2] = true;
		}
		if (tilePos == bot) {
			neighbours[3] = &tiles->at(i);
			hasNeighbour[3] = true;
		}
	}
}

void Tile::removeForNeighbours(std::vector<Tile>* tiles)
{
	for (int i = 0; i < 4; i++) {
		if (hasNeighbour[i]) {
			neighbours[i]->hasNeighbour[(i + 2 > 3) ? i - 2 : i + 2] = false;
			std::cout << ((i + 2 > 3) ? i - 2 : i + 2) << std::endl;
		}		
	}
}




void Tile::updateTileTex(TextureCache texCache,std::vector<Tile>* tiles) {

	bool left = false;
	bool right = false;
	bool top = false;
	bool bot = false;

	char floorType = _floor._type;



	if (hasNeighbour[0]) {
		if (neighbours[0]->_floor._type == floorType) {
			left = true;
		}
	}
	if (hasNeighbour[1]) {
		if (neighbours[1]->_floor._type == floorType) {
			top = true;
		}
	}
	if (hasNeighbour[2]) {
		if (neighbours[2]->_floor._type == floorType) {
			right = true;
		}
	}
	if (hasNeighbour[3]) {
		if (neighbours[3]->_floor._type == floorType) {
			bot = true;
		}
	}

	if (left && !right && !top && !bot) {
		_floor = Floor(texCache.getTexture("spaceTileLeft.png"), 1);
	}
	if (!left && right && !top && !bot) {
		_floor = Floor(texCache.getTexture("spaceTileRight.png"), 1);
	}
	if (!left && !right && top && !bot) {
		_floor = Floor(texCache.getTexture("spaceTileTop.png"), 1);
	}
	if (!left && !right && !top && bot) {
		_floor = Floor(texCache.getTexture("spaceTileBot.png"), 1);
	}
	if (left && right && !top && !bot) {
		_floor = Floor(texCache.getTexture("spaceTileRightLeft.png"), 1);
	}
	if (!left && !right && top && bot) {
		_floor = Floor(texCache.getTexture("spaceTileTopBot.png"), 1);
	}
	if (left && !right && top && !bot) {
		_floor = Floor(texCache.getTexture("spaceTileLeftTop.png"), 1);
	}
	if (!left && right && top && !bot) {
		_floor = Floor(texCache.getTexture("spaceTileRightTop.png"), 1);
	}
	if (!left && right && !top && bot) {
		_floor = Floor(texCache.getTexture("spaceTileRightBot.png"), 1);
	}
	if (left && !right && !top && bot) {
		_floor = Floor(texCache.getTexture("spaceTileLeftBot.png"), 1);
	}
	if (left && right && top && !bot) {
		_floor = Floor(texCache.getTexture("spaceTileRightTopLeft.png"), 1);
	}
	if (!left && right && top && bot) {
		_floor = Floor(texCache.getTexture("spaceTileLeftRightBot.png"), 1);
	}
	if (left && !right && top && bot) {
		_floor = Floor(texCache.getTexture("spaceTileLeftTopBot.png"), 1);
	}
	if (!left && right && top && bot) {
		_floor = Floor(texCache.getTexture("spaceTileRightTopBot.png"), 1);
	}
	if (!left && !right && !top && !bot) {
		_floor = Floor(texCache.getTexture("spaceTile.png"), 1);
	}
	if (left && right && top && bot) {
		_floor = Floor(texCache.getTexture("spaceTileOpen.png"), 1);
	}



}



