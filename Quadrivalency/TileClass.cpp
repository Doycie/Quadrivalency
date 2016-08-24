#include "TileClass.h"



TileClass::TileClass()
{
}

TileClass::TileClass(char floorType, TextureCache texCache, std::map<TilePos,TileClass>& tiles,int x, int y)
{
	if (floorType == 1) {	
		updateTileTex(tiles,texCache,x,y);
	}
}

char TileClass::getFloor(std::map<TilePos, TileClass>& tiles, int x, int y)
{

	TilePos a(x, y);
	auto tile = tiles.find(a);
	if (tile == tiles.end()) {
		return 0;
	}
	else {
		return tile->second._floor._type;
	}

}

void TileClass::updateTileTex(std::map<TilePos,TileClass>& tiles,TextureCache texCache,int x,int y)
{
			 bool left = false;
			 bool right = false;
			 bool top = false;
			 bool bot = false;
			 


			 if (_floor._type == getFloor(tiles, x + 1, y)) {
				 left = true;
			 }
			 if (_floor._type == getFloor(tiles, x, y + 1)) {
				 top = true;
			 }
			 if (_floor._type == getFloor(tiles, x, y - 1)) {
				 bot = true;
			 }
			 if (_floor._type == getFloor(tiles, x - 1, y)) {
				 right = true;
			 }

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


