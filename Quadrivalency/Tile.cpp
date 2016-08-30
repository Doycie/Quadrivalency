#include "Tile.h"
Tile::Tile() {
	_exist = false;
}

void Tile::init(char floorType, TextureCache texCache,Tile  tiles[1024], int x) {
	_type = floorType;
	_exist = true;
	updateTileTex(texCache,tiles,x );
}

void Tile::draw(SpriteBatch &spriteBatch, int x, int y) {

	int TiSi = 64;
	spriteBatch.draw(glm::vec4(x * TiSi, y*TiSi, TiSi, TiSi), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), _tex, 0.0f, ColorRGBA8(255, 255, 255, 255), 0.0f);
}


void Tile::updateTileTex(TextureCache texCache,Tile tiles[1024],int x) {

	bool left = false;
	bool right = false;
	bool top = false;
	bool bot = false;

	char floorType =  _type;

	if (tiles[x - 1]._exist && floorType == tiles[x - 1]._type)
		left = true;
	if (tiles[x + 1]._exist && floorType == tiles[x + 1]._type)
		right = true;
	if (tiles[(x)-32]._exist && floorType == tiles[x - 32]._type)
		top = true;
	if (tiles[x + 32]._exist && floorType == tiles[x + 32]._type)
		bot = true;

	if (left && !right && !top && !bot) {
		_tex  = texCache.getTexture("spaceTileLeft.png") ;
		return;
	}
	if (!left && right && !top && !bot) {
		_tex = texCache.getTexture("spaceTileRight.png");
		return;
	}
	if (!left && !right && top && !bot) {
		 _tex  = texCache.getTexture("spaceTileTop.png");
		return;
	}
	if (!left && !right && !top && bot) {
		_tex = texCache.getTexture("spaceTileBot.png");
		return;
	}
	if (left && right && !top && !bot) {
		_tex = texCache.getTexture("spaceTileRightLeft.png");
		return;
	}
	if (!left && !right && top && bot) {
		_tex = texCache.getTexture("spaceTileTopBot.png");
		return;
	}
	if (left && !right && top && !bot) {
		_tex = texCache.getTexture("spaceTileLeftTop.png");
		return;
	}
	if (!left && right && top && !bot) {
		_tex = texCache.getTexture("spaceTileRightTop.png");
		return;
	}
	if (!left && right && !top && bot) {
		_tex = texCache.getTexture("spaceTileRightBot.png");
		return;
	}
	if (left && !right && !top && bot) {
		_tex = texCache.getTexture("spaceTileLeftBot.png");
		return;
	}
	if (left && right && top && !bot) {
		_tex = texCache.getTexture("spaceTileRightTopLeft.png");
		return;
	}
	if (!left && right && top && bot) {
		_tex = texCache.getTexture("spaceTileRightTopBot.png");
		return;
	}
	if (left && !right && top && bot) {
		_tex = texCache.getTexture("spaceTileLeftTopBot.png");
		return;
	}
	if (left && right && !top && bot) {
		_tex = texCache.getTexture("spaceTileLeftRightBot.png");
		return;
	}
	if (!left && !right && !top && !bot) {
		_tex = texCache.getTexture("spaceTile.png");
		return;
	}
	if (left && right && top && bot) {
		_tex = texCache.getTexture("spaceTileOpen.png");
		return;
	}



}



