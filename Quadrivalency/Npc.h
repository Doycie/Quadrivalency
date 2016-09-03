#pragma once
#include "SpriteBatch.h"
#include "TextureCache.h"
#include "Tile.h"
class Npc
{
public:
	Npc(TextureCache texCache);
	~Npc();

	void update(Tile tiles[1024]);
	void draw(SpriteBatch &spriteBatch);

	void setTargetTile(int x);

private:

	struct Node {
		Node(Node *parent,int x, float f, float g, float h ) {
			_parent = parent;
			_x = x;
			_f = f;
			_g = g;
			_h = h;
		}
		Node *_parent;
		int _x;
		float _f,_g, _h;
	};
	void findPath(Tile tiles[1024]);

	int _xTile;
	
	int _x;
	int _y;

	std::vector<int> path;

	GLuint _tex;
	float _angle;

	
};

