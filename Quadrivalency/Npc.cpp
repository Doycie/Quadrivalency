#include "Npc.h"
#include "Math.h"


Npc::Npc(TextureCache texCache)
{
	_tex = texCache.getTexture("Npc.png");
	_angle = 0;
	_x = 1024;
	_y = 1024;
	_xTile = 512;
}


Npc::~Npc()
{
}


void Npc::update(Tile tiles[1024])
{

	
	int currentTile = _x / 64 + (_y / 64) * 32;
	
	if (currentTile != _xTile) {
		
		path = PathFinder::findPath(tiles, currentTile, _xTile);
	}
	else if (!path.empty()) {
		path.clear();
	}


}

void Npc::draw(SpriteBatch &spriteBatch) {
	spriteBatch.draw(glm::vec4(_x,_y,32,32),glm::vec4(0.0f,0.0f,1.0f,1.0f),_tex,1.0f,ColorRGBA8(255,255,255,255),_angle);
	for (std::vector<int>::iterator it = path.begin(); it != path.end(); it++) {
		int dx = (*it % 32)*64;
		int dy = floor(*it / 32)*64;
		
		spriteBatch.draw(glm::vec4(dx, dy, 32, 32), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), _tex, 1.0f, ColorRGBA8(255, 255, 255, 255), _angle);
	}
}

void Npc::setTargetTile(int x)
{
	_xTile = x;
	
}