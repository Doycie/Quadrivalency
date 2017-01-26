#pragma once
#include "SpriteBatch.h"
#include "TextureCache.h"
#include <cstdlib>
#include <list>


struct Positionbla {
	Positionbla() :x(0), y(0) {}
	Positionbla(int px, int py) :x(px), y(py) {}
	int x, y;
	bool operator==(const Positionbla& p1) {
		if (x == p1.x && y == p1.y)
			return true;
		return false;
	}
};

struct Star
{
	Star() :x(0), y(0), type(0), size(0) {}
	Star(int px, int py, int myType, int mySize) :x(px), y(py), type(myType), size(mySize) {}
	int x, y, type, size;
};

class Starmap {

public:

	Starmap();
	
	~Starmap();

	void init(TextureCache texCache);

	void draw(SpriteBatch &spriteBatch);

	void update(Positionbla pos);

private: 
	static const int _amountOfStarTypes = 4;


	void renderToTexture(SpriteBatch &spriteBatch);

	//random seed to generate
	int _seed = 213312;

	//dimensions of a sector
	int _length = 400;

	//amount of stars in a sector
	int _amount = 1000;

	GLuint _starSprite[_amountOfStarTypes];

	std::list<Star>::const_iterator iterator;

	std::list<Star> _currentSector;
//	std::map<Positionbla, std::list<Star>>  _sectors;

	void GenerateSector(Positionbla pos);
};