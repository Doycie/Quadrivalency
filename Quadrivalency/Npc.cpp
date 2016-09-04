#include "Npc.h"
#include "Math.h"


Npc::Npc(TextureCache texCache)
{
	_tex = texCache.getTexture("Npc.png");
	_angle = 0;
	_x = 1024;
	_y = 1024;
	_xTile = Utility::getXFromYAndX(_x, _y);
}


Npc::~Npc()
{
}


void Npc::update()
{
	int currentTile = getTile();
	
	 if (!path.empty()) {
		int targetX = Utility::getXFromInt(path.back());
		int targetY = Utility::getYFromInt(path.back());
		
		float angle = atan2((targetY - _y),(targetX - _x));
		

		_x += movementSpeed * cos(angle);
		_y += movementSpeed * sin(angle);

		float distanceToDestination = sqrt((_x - targetX)*(_x - targetX) + (_y - targetY)*(_y - targetY));

		if (distanceToDestination < movementSpeed) {

			if (path.size() == 1) {
				_x = targetX;
				_y = targetY;

				path.clear();
			}
			else
				path.erase(path.end() - 1);
		}

	}


}

void Npc::draw(SpriteBatch &spriteBatch) {
	spriteBatch.draw(glm::vec4(_x,_y,32,32),glm::vec4(0.0f,0.0f,1.0f,1.0f),_tex,1.0f,ColorRGBA8(255,255,255,255),_angle);
//	for (std::vector<int>::iterator it = path.begin(); it != path.end(); it++) {
	//	int dx = (*it % 32)*64;
//int dy = floor(*it / 32)*64;
		
	//	spriteBatch.draw(glm::vec4(dx, dy, 32, 32), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), _tex, 1.0f, ColorRGBA8(255, 255, 255, 255), _angle);
//	}
}

void Npc::setPath(int x, Tile tiles[1024])
{
	path = PathFinder::findPath(tiles, getTile(), x);
}

int Npc::getTile() {
	return  _x / 64 + (_y / 64) * 32;
};