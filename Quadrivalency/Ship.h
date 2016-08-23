#pragma once
#include <glm\glm.hpp>
#include <vector>
#include "SpriteBatch.h"
#include "TextureCache.h"

struct Walls {
	char left;
	char right;
	char up;
	char down;
};

struct Floor {
	Floor(GLuint tex,char type) {
		_tex = tex;
		_type = type;
	}
	Floor() : _tex(0), _type(0) {}
	GLuint _tex;
	char _type;
};

struct Module {

};

struct Tile {
	Tile(char floorType,TextureCache texCache,int x, int y) {
		if (floorType == 1) {
			 _floor = Floor(texCache.getTexture("image.png"),1);
		}
		_x = x;
		_y = y;

	}
	
	int TiSi = 64;
	int _x, _y;
	Floor _floor;
	Module _module;
	
	Walls walls;

	void draw(SpriteBatch &spriteBatch) {
		//std::cout << _floor._tex << std::endl;
		
		spriteBatch.draw(glm::vec4(0.0f, 0.0f, 600.0f, 800.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),1, 0.0f, ColorRGBA8(255.0f, 255.0f, 255.0f, 255.0f), 0.0f);



		spriteBatch.draw(glm::vec4(_x * TiSi, _y*TiSi, TiSi, TiSi), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), _floor._tex, 0.0f, ColorRGBA8(255, 255, 255, 255), 0.0f);

	}

};

class Ship
{
public:
	Ship();
	~Ship();

	void draw(SpriteBatch& spriteBatch);
	void update();
	void addTile(char floorType, TextureCache texCache, glm::vec2 coords);

private:

	std::vector<Tile> _tiles;

};

