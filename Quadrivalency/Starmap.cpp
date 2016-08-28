#include "Starmap.h"


Starmap::Starmap(TextureCache texCache)
{
	_starSprite = texCache.getTexture("star.png");
	GenerateSector(Positionbla(0,0));
	update(Positionbla(0, 0));
}

Starmap::~Starmap()
{

}

void Starmap::draw(SpriteBatch &spriteBatch)
{
	int TiSi = 16;

	for (iterator = _currentSector.begin(); iterator != _currentSector.end(); ++iterator) {
		Star currentStar = *iterator;
		spriteBatch.draw(glm::vec4(currentStar.x * TiSi, currentStar.y*TiSi, TiSi, TiSi), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), _starSprite, 0.0f, ColorRGBA8(255, 255, 255, 5), 0.0f);
	}
}

void Starmap::GenerateSector(Positionbla pos)
{
//	std::list<Star> sector;
	srand(_seed);
	for (int i = 0; i < _amount; i++) {
		Star star = Star(rand() % _length, rand() % _length, 0);
		_currentSector.push_back(star);
	}
//	_sectors.insert(std::pair<Pos, std::list<Star>>(pos, sector));
}
void Starmap::update(Positionbla pos) {
//	_currentSector = _sectors[pos];
}

