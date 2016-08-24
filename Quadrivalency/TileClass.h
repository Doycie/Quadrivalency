#pragma once

#include "TextureCache.h"
#include "SpriteBatch.h"

struct TilePos {

	TilePos(int x, int y) {
		_x = x;
		_y = y;
	}
	int _x;
	int _y;

	inline bool operator<(const TilePos& v) const {
		if ((_x < v._x && _y < v._y ) && 
			!(((_x > v._x) && (_y > v._y)) || 
			((_x < v._x) && (_y > v._y)) || 
			((_x > v._x) && (_y < v._y)))
			) 
		{
			return true;
		}
		return false;
	}
	//inline bool operator==(const TilePos& v) const {
	//	if (_x == v._x && _y == v._y) {
	//		return true;
	//	}
	//	return false;
	//}

	/*
	bool operator==(const TilePos& v) const {
		if (_x == v._x && _y == v._y) {
			return true;
		}
		return false;
	}*/
	//bool operator>(const TilePos& v) const { if (_x == v._x && _y == v._y) return false; return true; }
	
	

};

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


class TileClass {

public:

	TileClass();
	TileClass(char floorType, TextureCache texCache, std::map<TilePos, TileClass>& tiles,int x,int y);

	char getFloor(std::map<TilePos, TileClass>& tiles, int x, int y);

	int TiSi = 64;
	
	Floor _floor;
	Module _module;

	Walls walls;

	void updateTileTex(std::map<TilePos, TileClass>& tiles, TextureCache texCache, int x, int y);

	void draw(SpriteBatch &spriteBatch, int x,int y) {
		//std::cout << _floor._tex << std::endl;


		spriteBatch.draw(glm::vec4(x * TiSi, y*TiSi, TiSi, TiSi), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), _floor._tex, 0.0f, ColorRGBA8(255, 255, 255, 5), 0.0f);

	}
private:

};