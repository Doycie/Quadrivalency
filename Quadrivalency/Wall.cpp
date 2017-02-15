#include "Wall.h"



Wall::Wall()
{
}


Wall::~Wall()
{
}

void Wall::init(glm::vec2 position, glm::vec2 size, b2World * world, TextureCache &texCache)
{
	StaticEntity::init( position,size,  world,  texCache);
	_tex = texCache.getTexture("image.png");
}