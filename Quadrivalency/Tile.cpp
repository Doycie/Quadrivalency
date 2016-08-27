#include "Tile.h"


Tile::Tile(char floorType, TextureCache texCache, std::vector<Tile>& tiles, Pos position) {
	_floor._type = floorType;
	pos = position;
	
	Pos left(pos.x -1,pos.y);
	Pos right(pos.x + 1, pos.y);
	Pos bot(pos.x, pos.y - 1);
	Pos top(pos.x, pos.y + 1);


	for (int i = 0; i < tiles.size(); i++) {
		Pos tilePos = tiles[i].pos;

		if (tilePos == left)
			neighbours[0] = &tiles[i];
		if (tilePos == top)
			neighbours[1] = &tiles[i];
		if (tilePos == right)
			neighbours[2] = &tiles[i];
		if (tilePos == bot)
			neighbours[3] = &tiles[i];

	}
	

	if (floorType == 1) {
		updateTileTex(texCache);
	}
}

void Tile::draw(SpriteBatch &spriteBatch, int x, int y) {
	int TiSi = 64;
	spriteBatch.draw(glm::vec4(x * TiSi, y*TiSi, TiSi, TiSi), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), _floor._tex, 0.0f, ColorRGBA8(255, 255, 255, 5), 0.0f);
}

void Tile::updateTileTex(TextureCache texCache) {

	bool left = false;
	bool right = false;
	bool top = false;
	bool bot = false;

	char floorType = _floor._type;

	if (neighbours[0] != nullptr)
		if (neighbours[0]->_floor._type == floorType)
			left == true;
	if (neighbours[1] != nullptr)
		if (neighbours[1]->_floor._type == floorType)
			top == true;
	if (neighbours[0] != nullptr)
		if (neighbours[0]->_floor._type == floorType)
			right == true;
	if (neighbours[0] != nullptr)
		if (neighbours[0]->_floor._type == floorType)
			bot == true;

	if (left && !right && top && bot) {
		_floor = Floor(texCache.getTexture("spaceTileLeft.png"), 1);
	}
	if (!left && right && top && bot) {
		_floor = Floor(texCache.getTexture("spaceTileRight.png"), 1);
	}
	if (left && right && top && !bot) {
		_floor = Floor(texCache.getTexture("spaceTileTop.png"), 1);
	}
	if (left && right && !top && bot) {
		_floor = Floor(texCache.getTexture("spaceTileBot.png"), 1);
	}
	if (!left && !right && top && bot) {
		_floor = Floor(texCache.getTexture("spaceTileRightLeft.png"), 1);
	}
	if (left && right && !top && !bot) {
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
	if (!left && !right && top && !bot) {
		_floor = Floor(texCache.getTexture("spaceTileRightTopLeft.png"), 1);
	}
	if (!left && !right && !top && bot) {
		_floor = Floor(texCache.getTexture("spaceTileLeftRightBot.png"), 1);
	}
	if (left && !right && !top && !bot) {
		_floor = Floor(texCache.getTexture("spaceTileLeftTopBot.png"), 1);
	}
	if (!left && right && !top && !bot) {
		_floor = Floor(texCache.getTexture("spaceTileRightTopBot.png"), 1);
	}
	if (!left && !right && !top && !bot) {
		_floor = Floor(texCache.getTexture("spaceTileOpen.png"), 1);
	}
	if (left && right && top && bot) {
		_floor = Floor(texCache.getTexture("spaceTile.png"), 1);
	}
}



