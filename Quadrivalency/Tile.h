#pragma once

#include "TextureCache.h"
#include "SpriteBatch.h"



class Tile {

public:

	Tile();

	void init(char floorType, TextureCache texCache, Tile tiles[1024], int x);
	bool _exist;

	void draw(SpriteBatch &spriteBatch, int x, int y);
	void updateTileTex(TextureCache texCache, Tile tiles[1024],int x);


private:

	GLuint _tex;
	char _type;

};