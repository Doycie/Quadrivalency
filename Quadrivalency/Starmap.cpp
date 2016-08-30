#include "Starmap.h"
#include <string> 


Starmap::Starmap(TextureCache texCache)
{
	for (int i = 0; i < _amountOfStarTypes; i++) {
		_starSprite[i] = texCache.getTexture("star" + std::to_string(i) + ".png");
	}
	GenerateSector(Positionbla(0,0));
	update(Positionbla(0, 0));
}

Starmap::~Starmap()
{

}

void Starmap::draw(SpriteBatch &spriteBatch)
{
	int TiSi_BASE = 16;
	int TiSi = TiSi_BASE;
	for (iterator = _currentSector.begin(); iterator != _currentSector.end(); ++iterator) {
		Star currentStar = *iterator;
		TiSi = TiSi_BASE*currentStar.size;
		spriteBatch.draw(glm::vec4(currentStar.x * TiSi, currentStar.y*TiSi, TiSi, TiSi), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), _starSprite[currentStar.type], 0.0f, ColorRGBA8(255, 255, 255, 255), 0.0f);
	}
}

void Starmap::GenerateSector(Positionbla pos)
{
//	std::list<Star> sector;
	srand(_seed);
	for (int i = 0; i < _amount; i++) {
		Star star = Star(rand() % _length - _length * 0.5, rand() % _length - _length * 0.5, rand() % 4, rand() % 5 + 1);
		_currentSector.push_back(star);
	}
//	_sectors.insert(std::pair<Pos, std::list<Star>>(pos, sector));
}
void Starmap::update(Positionbla pos) {
//	_currentSector = _sectors[pos];
}

