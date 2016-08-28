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
	Star() :x(0), y(0), type(0) {}
	Star(int px, int py, int myType) :x(px), y(py), type(myType) {}
	int x, y, type;
};

class Starmap {

public:
	Starmap(TextureCache texCache);
	~Starmap();

	void draw(SpriteBatch &spriteBatch);

	void update(Positionbla pos);

private: 
	//random seed to generate
	int _seed = 213312;

	//dimensions of a sector
	int _length = 100;

	//amount of stars in a sector
	int _amount = 500;

	GLuint _starSprite;

	std::list<Star>::const_iterator iterator;

	std::list<Star> _currentSector;
//	std::map<Positionbla, std::list<Star>>  _sectors;

	void GenerateSector(Positionbla pos);
};