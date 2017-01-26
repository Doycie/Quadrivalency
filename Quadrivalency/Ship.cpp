#include "Ship.h"



Ship::Ship()
{
}


Ship::~Ship()
{

}

void Ship::init(TextureCache texCache) {
	addTile(1, texCache, (32 * 16) + 16);

	addTile(1, texCache, (32 * 17) + 16);
	addTile(1, texCache, (32 * 16) + 17);
	addTile(1, texCache, (32 * 17) + 17);

	addTile(1, texCache, (32 * 15) + 16);
	addTile(1, texCache, (32 * 15) + 15);
	addTile(1, texCache, (32 * 16) + 15);

	addTile(1, texCache, (32 * 15) + 17);
	addTile(1, texCache, (32 * 17) + 15);

	npcs.push_back(Npc(texCache));
}

void Ship::addTile(char floorType, TextureCache texCache, int x)
{


	if (x <= 1024 && x >= 0) {
		if (tiles[x]._exist) {
			tiles[x]._exist = false;
		}
		else {
			tiles[x].init(floorType, texCache, tiles, x);
			tiles[x]._exist = true;
		}

		if (x > 0) {
			tiles[tiles, x - 1].updateTileTex(texCache, tiles, x - 1);
		}

		if (x < 1024) {
			tiles[tiles, x + 1].updateTileTex(texCache, tiles, x + 1);
		}

		if (x > 31)
		{
			tiles[tiles, x - 32].updateTileTex(texCache, tiles, x - 32);
		}

		if (x < 992) {
			tiles[tiles, x + 32].updateTileTex(texCache, tiles, x + 32);
		}
	}
}


void Ship::update() {
	
}

void Ship::draw(SpriteBatch &spriteBatch) {
	
	for (int i = 0; i < 1024; i++) {
		if(tiles[i]._exist)
		tiles[i].draw(spriteBatch, i % 32, (int)i / 32);
	}
	for (std::vector<Npc>::iterator it = npcs.begin(); it != npcs.end(); it++) {
		it->draw(spriteBatch);
	}

}