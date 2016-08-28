#pragma once

#include "TextureCache.h"
#include "SpriteBatch.h"



struct Walls {
	char left;
	char right;
	char up;
	char down;
};

struct Floor {
	Floor(GLuint tex, char type) {
		_tex = tex;
		_type = type;
	}
	Floor() : _tex(0), _type(0) {}
	GLuint _tex;
	char _type;
};

struct Module {

};
struct Pos {
	Pos() :x(0), y(0) {}
	Pos(int px, int py) :x(px), y(py) {}
	int x, y;
	bool operator==(const Pos& p1) {
		if (x == p1.x && y == p1.y)
			return true;
		return false;
	}
};



class Tile {

public:

	Tile(char floorType, TextureCache texCache, std::vector<Tile>& tiles, Pos position);


	Floor _floor;
	Module _module;
	Walls walls;
	Pos _pos;

	void draw(SpriteBatch &spriteBatch, int x, int y);
	void updateNeighbours(std::vector<Tile>& tiles);
	void removeForNeighbours(std::vector<Tile>& tiles);

private:
	void updateTileTex(TextureCache texCache,  std::vector<Tile> tiles);
	
	Tile* neighbours[3];
	bool hasNeighbour[3];


};